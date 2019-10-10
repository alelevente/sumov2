//
// Created by levente on 2019.09.16..
//

#include <fstream>
#include <libsumo/Edge.h>
#include "ECNJudge.h"
#include "LPSolver/LPSolver.h"
#include "ECNConflictClass.h"
#include "microsim/devices/GroupingSystem/Group.h"
#include "microsim/devices/MessagingSystem/Messenger.h"
#include "JudgeSystem.h"

#define MAGIC_CONST 0.018


ECNJudge::ECNJudge(const std::string &path) {
    auto* active = new ECNConflictClass();
    auto* waiting = new ECNConflictClass();
    conflictClasses.insert(conflictClasses.end(), active);
    conflictClasses.insert(conflictClasses.end(), waiting);
    active->setColor(false);
    waiting->setColor(true);
    activeCC = 0;
    lastChanged = 0;
    now = -1; lastChanged = -1; yellowStarted = -1; lastECN = -1; lastStepLengthCalc = -1;

    std::ifstream input(path, std::ifstream::in);
    int n, r;
    input >> n;
    nDirections = n;
    //std::vector<std::string> readDirections;
    std::string rDirection;
    for (int i=0; i<n; ++i){
        input >> rDirection;
        directionTimes.insert(std::make_pair(rDirection, -i));
        directions.insert(std::make_pair(rDirection, i));
        std::cout << directionTimes[rDirection] << std::endl;
    }
    //Make a Descartes product of the directions:
    /*std::string currentDirection = "";
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j) {
            currentDirection = readDirections[i]+"-"+readDirections[j];
            directionTimes.insert(std::make_pair(currentDirection, 0));
            directions.insert(std::make_pair(currentDirection, i*n+j));
        }
    }*/
    candidatesForNextActivePhase = new bool[n*n];
    for (int i=0; i<n; ++i) candidatesForNextActivePhase[i] = false;
    conflictMtx=new int*[n];
    for (int i=0; i<n; ++i){
        int* b = new int[n];
        for (int j=0; j<n; ++j){
            input >> r;
            b[j] = r;
        }
        conflictMtx[i] = b;
    }
    conflictMtx[0][0] = n;

    double rDouble;
    input >> r;
    std::string rDirection2;
    for (int i=0; i<r; ++i){
        input >> rDirection;
        input >> rDouble;
        myPortLimitMap.insert(std::make_pair(rDirection, rDouble));
        portDirections.insert(portDirections.end(), rDirection);
    }
    input >> r;
    for (int i=0; i<r; ++i){
        input >> rDirection;
        input >> rDirection2;
        directionToPortMap.insert(std::make_pair(rDirection, rDirection2));
    }

    this->initialized = true;
}

ECNJudge::~ECNJudge() {
    delete[] conflictMtx;
    delete[] candidatesForNextActivePhase;
}

void ECNJudge::step(const SUMOTime &st) {
    now = st;
    calculateStepLength();
    informOthers();
    if (now-lastChanged>stepLength && !yellow) {
        calculateCandidates();
        changeCC();
    } else if (yellow && now-yellowStarted>3000) {
        makeGreen();
    }
}

bool ECNJudge::canPass(MSDevice_SAL *who, const std::string &direction) {
    return ((ECNConflictClass*)conflictClasses[0])->containsDirection(direction);
}

int ECNJudge::decideCC(Group *group, const std::string &direction) {
    //updating the list of cars and directions:
    Messenger** messengers = group->getMembers();
    int nMessengers = group->getNMembers();
    for (int i=0; i<nMessengers; ++i) {
        directionByCars.insert(std::make_pair(messengers[i]->mySAL, direction));
    }
    return ((ECNConflictClass*)conflictClasses[0])->containsDirection(direction)?0:1;
}

void ECNJudge::changeCC() {
    if (!candidatesCalculated) calculateCandidates();
    //At first, let's update the list of cars and directions
    //And also collect the cars who will not have to stop by the change:
    std::vector<MSDevice_SAL*> notChanging;
    for (auto& item: directionByCars) {
        if (!(conflictClasses[0]->hasVehicle(item.first))){
            if (!(conflictClasses[1]->hasVehicle(item.first))) directionByCars.erase(item.first);
        } else {
            //Active and will not be inactive in the next run:
            if (candidatesForNextActivePhase[directions[item.second]]) {
                notChanging.insert(notChanging.end(), item.first);
            }
        }


    }
    ECNConflictClass* activeCC = ((ECNConflictClass*)conflictClasses[0]);
    ECNConflictClass* inactiveCC = ((ECNConflictClass*)conflictClasses[1]);
    //std::cout << this->directions.at(0)+" flagged yellow" << std::endl;
    activeCC->setNextList(notChanging);
    activeCC->informCars(JC_STOP);
    activeCC->resetNextCars();
    yellow = true;
    yellowStarted = now;
    candidatesCalculated = false;
}

bool mapContainsValue(const std::map<MSDevice_SAL*, std::string>& map, const std::string& str){
    for (auto& s: map) {
        if (s.second == str) return true;
    }
    return false;
}

bool mapContainsValue(const std::map<std::string, std::string>& map, const std::string& str){
    for (auto& s: map) {
        if (s.second == str) return true;
    }
    return false;
}

bool listContainsValue(const std::vector<std::string> vector, const std::string& value){
    auto it = std::find(vector.begin(), vector.end(), value);
    return it != vector.end();
}

void ECNJudge::calculateCandidates() {
    std::string longestIdx;
    SUMOTime longest = 0;
    for (auto& e: directionTimes) {
        if (now-e.second > longest) {
            //std::map<MSDevice_SAL*, std::string>::iterator hasCars = directionByCars.find(e.first);//std::find(directionByCars.begin(), directionByCars.end(), e.first);
            if (mapContainsValue(directionByCars, e.first)) {
                std::string port = directionToPortMap[e.first];
                ECNJudge* neigh = nullptr;
                for (auto p: portMap) if (p.second == port) neigh = p.first;
                if (!congestionMap[neigh]) {
                    longest = now - e.second;
                    longestIdx = e.first;
                }
            }
        }
    }

    std::cout << longestIdx <<": " << longest << std::endl;

    int* addConstraints = new int[conflictMtx[0][0]];
    for (int i=0; i<conflictMtx[0][0]; ++i){
        std::string dir = "";
        for (auto d: directions) if (d.second==i) dir = d.first;
        std::string port = directionToPortMap[dir];
        ECNJudge* neigh = nullptr;
        for (auto p: portMap) if (p.second == port) neigh = p.first;
        if (!congestionMap[neigh]) {
            addConstraints[i] = -1;
        } else addConstraints[i] = 0;
    }
    addConstraints[directions[longestIdx]] = 1;
    LPSolver* lpSolver = new LPSolver();
    auto solution = lpSolver->getLPSolution(conflictMtx, addConstraints);
    for (int i=0; i<conflictMtx[0][0]; ++i){
        candidatesForNextActivePhase[i] = solution[i] != 0;
    }
    delete lpSolver;
    candidatesCalculated = true;
}

void ECNJudge::makeGreen() {
    //std::cout << this->directions[0] << " makes green" << std::endl;
    ECNConflictClass* activeCC = ((ECNConflictClass*)conflictClasses[0]);
    ECNConflictClass* inactiveCC = ((ECNConflictClass*)conflictClasses[1]);
    activeCC->clearDirections();
    inactiveCC->clearDirections();
    activeCC->removeAllVehicles();
    inactiveCC->removeAllVehicles();
    for (auto& item: directions){
        if (candidatesForNextActivePhase[item.second]) {
            activeCC->addDirection(item.first);
            std::cout << item.first << std::endl;
            directionTimes[item.first] = now;
        } else {
            inactiveCC->addDirection(item.first);
        }
    }
    for (auto& item: directionByCars) {
        if (activeCC->containsDirection(item.second)){
            activeCC->addVehicle(item.first);
            Group* group= item.first->getGroup();
            if (group != nullptr) item.first->getGroup()->setMyCC(activeCC);
        } else {
            inactiveCC->addVehicle(item.first);
            Group* group= item.first->getGroup();
            if (group!= nullptr) group->setMyCC(inactiveCC);
        }
    }
    activeCC->informCars(JC_GO);
    lastChanged = now;
    yellow = false;
}

void ECNJudge::carLeftJunction(MSDevice_SAL *who, bool byForce) {
    AbstractJudge::carLeftJunction(who, byForce);
    directionByCars.erase(who);
    conflictClasses[0]->removeVehicle(who);
    conflictClasses[1]->removeVehicle(who);
}



void ECNJudge::informJudge(void *message) {
    ECNNotification* notification = (ECNNotification*) message;
    if (notification->congested) std::cout << "Notification arrived" << std::endl;
    auto neighbor = portMap.find(notification->sender);
    if (neighbor != portMap.end()){
        if (notification->congested) std::cout << "neighbour found "<< notification->direction << neighbor->second << std::endl;
        if (notification->direction == neighbor->second) {
            congestionMap.erase(notification->sender);
            congestionMap.insert(std::make_pair(notification->sender, notification->congested));
        }
    }
}

void ECNJudge::addNeighbourPort(ECNJudge *neighbor, const std::string &port) {
    portMap.insert(std::make_pair(neighbor, port));

}

void ECNJudge::informOthers() {
    if (now-lastECN < 15000) return;
    double occup;
    bool cong = false;
    for (auto& pl: myPortLimitMap) {
        occup = libsumo::Edge::getLastStepOccupancy(pl.first);
        std::cout << "Occupancy: " << occup << std::endl;
        cong = (occup > MAGIC_CONST*pl.second);
        auto* notification = new ECNNotification();
        notification->congested = cong;
        notification->sender = this;
        notification->direction = pl.first;
        JudgeSystem::getInstance().informJudges(notification);
    }
    lastECN = now;
}

std::string getDirectionFromPort(const std::map<std::string, std::string>& dirToPortMap, const std::string& port){
    for(auto it = dirToPortMap.begin(); it != dirToPortMap.end(); ++it){
        if (it->second == port) return it->first;
    }
    return "";
}

void ECNJudge::calculateStepLength() {
    if (now-lastStepLengthCalc < 2500 && stepLength!=0) return;
    int vehs;
    int max = 0;
    for (auto& d: portDirections) {
        vehs = libsumo::Edge::getLastStepVehicleNumber(d);
        if (vehs > max) {
            stepLength = 5000 + vehs * 1500 > 40000 ? 40000 : 5000 + vehs * 1500;
            max = vehs;
        }
    }
    auto* active = (ECNConflictClass*)conflictClasses[0];
    for (auto& d: portMap) {
        auto& neighbor = d.first;
        if (congestionMap[neighbor]) std::cout << d.second << " congested" << std::endl; // else std::cout << "check was" << std::endl;
        if (congestionMap[neighbor] && listContainsValue(active->directionList, getDirectionFromPort(directionToPortMap,d.second))) {
            stepLength = 5000;
            lastStepLengthCalc = now;
            std::cout << "TIME REDUCED! :)" << std::endl;
            return;
        }
    }
    lastStepLengthCalc = now;
}