//
// Created by levente on 2019.09.16..
//

#include <fstream>
#include "ECNJudge.h"
#include "LPSolver/LPSolver.h"
#include "ECNConflictClass.h"
#include "microsim/devices/GroupingSystem/Group.h"
#include "microsim/devices/MessagingSystem/Messenger.h"


ECNJudge::ECNJudge(const std::string &path) {
    std::ifstream input(path, std::ifstream::in);
    int n, r;
    input >> n;
    nDirections = n;
    std::vector<std::string> readDirections;
    std::string rDirection;
    for (int i=0; i<n; ++i){
        input >> rDirection;
        readDirections.insert(readDirections.end(), rDirection);
    }
    //Make a Descartes product of the directions:
    std::string currentDirection = "";
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j) {
            currentDirection = readDirections[i]+"-"+readDirections[j];
            directionTimes.insert(std::make_pair(currentDirection, 0));
            directions.insert(std::make_pair(currentDirection, i*n+j));
        }
    }
    candidatesForNextActivePhase = new bool[n*n];
    for (int i=0; i<n; ++i) candidatesForNextActivePhase[i] = false;
    int** conflictMtx=new int*[n];
    for (int i=0; i<n; ++i){
        int* b = new int[n];
        for (int j=0; j<n; ++j){
            input >> r;
            b[j] = r;
        }
        conflictMtx[i] = b;
    }
    conflictMtx[0][0] = n;

    auto* active = new ECNConflictClass();
    auto* waiting = new ECNConflictClass();
    conflictClasses.insert(conflictClasses.end(), active);
    conflictClasses.insert(conflictClasses.end(), waiting);
}

ECNJudge::~ECNJudge() {
    delete[] conflictMtx;
    delete[] candidatesForNextActivePhase;
}

void ECNJudge::step(const SUMOTime &st) {
    now = st;
    if (!candidatesCalculated && lastChanged>20) {
        calculateCandidates();
        changeCC();
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
    activeCC->setNextList(notChanging);
    activeCC->informCars(JC_STOP);
    activeCC->clearDirections();
    inactiveCC->clearDirections();
    activeCC->removeAllVehicles();
    inactiveCC->removeAllVehicles();
    for (auto& item: directions){
        if (candidatesForNextActivePhase[item.second]) {
            activeCC->addDirection(item.first);
            directionTimes[item.first] = now;
        }
    }
    for (auto& item: directionByCars) {
        if (activeCC->containsDirection(item.second)){
            activeCC->addVehicle(item.first);
            item.first->getGroup()->setMyCC(activeCC);
        } else {
            inactiveCC->addVehicle(item.first);
            item.first->getGroup()->setMyCC(inactiveCC);
        }
    }
    candidatesCalculated = false;
    lastChanged = now;
}

void ECNJudge::calculateCandidates() {
    std::string longestIdx;
    SUMOTime longest = 0;
    for (auto& e: directionTimes) {
        if (now-e.second > longest) {
            longest = e.second;
            longestIdx = e.first;
        }
    }

    int* addConstraints = new int[conflictMtx[0][0]];
    addConstraints[directions[longestIdx]] = 1;
    LPSolver* lpSolver = new LPSolver();
    auto solution = lpSolver->getLPSolution(conflictMtx, addConstraints);
    for (int i=0; i<conflictMtx[0][0]; ++i){
        candidatesForNextActivePhase[i] = solution[i];
    }
    delete lpSolver;
    candidatesCalculated = true;
}