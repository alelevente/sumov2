//
// Created by levente on 2018.07.31..
//


#include "ConflictClass.h"
#include "microsim/devices/MessagingSystem/Messenger.h"
#include <libsumo/Vehicle.h>

ConflictClass::ConflictClass(int dangerRadius) {
    myColor.a = 255;
    myColor.r = rand() % 256;
    myColor.g = rand() % 256;
    myColor.b = rand() % 256;
    inDanger = dangerRadius;
}

ConflictClass::ConflictClass() {
    myColor.a = 255;
    inDanger = 35;
    myColor.r = rand() % 256;
    myColor.g = rand() % 256;
    myColor.b = rand() % 256;
}

const libsumo::TraCIColor& ConflictClass::getMyColor() {
    return myColor;
}

void ConflictClass::joinGroup(Group *group) {
    Messenger** msgs = group->getMembers();
    for (int i=0; i<group->getNMembers(); ++i) {
        addVehicle(msgs[i]->mySAL);
    }
}
void ConflictClass::addVehicle(MSDevice_SAL *sal) {
    if (!hasVehicle(sal)) {
        myCars.insert(myCars.end(), sal);
        Group* g = sal->getGroup();
        if (g!= nullptr) {
            auto it = groupIDs.find(g);
            if (it == groupIDs.end()) groupIDs.insert(std::make_pair(g, g->getMyGroupID()));
            sal->setVehicleColor(myColor);
        }

    }
}

void ConflictClass::removeVehicle(MSDevice_SAL *sal) {
    if (myCars.empty()) return;
    /*auto i = myCars.begin();
    if (*i == nullptr) return;
    while (*i != sal && i != myCars.end()) ++i;
    if ((*i) == sal) {
        //(*i) = nullptr;
        myCars.erase(i);
    }*/
    auto i = std::find(myCars.begin(), myCars.end(), sal);
    if (i != myCars.end()) myCars.erase(i);
}

bool ConflictClass::hasVehicle(MSDevice_SAL *vehicle) {
    if (myCars.empty()) return false;
    auto i = std::find(myCars.begin(), myCars.end(), vehicle);
    return i != myCars.end();
}

bool ConflictClass::canJoinGroup(int nMembers, const std::string &inDirection, const std::string &outDirection) {
    return true;
}

double ConflictClass::calculatePrice() {
    return 0;
}

bool ConflictClass::isEmpty() {
    return myCars.size() == 0;
}

bool ConflictClass::isFirst() {
    for (auto x: myCars)
    {
        if (x->isFirst()) return true;
    }
    return false;
}

bool ConflictClass::isThereCarInDanger(double x, double y) {
    Position pos;
    for (auto i: myCars) {
        pos = (*i).getHolder().getPosition(0);
        if (sqrt(pow(pos.x()-x, 2)+pow(pos.y()-y,2)) < IN_DANGER &&
                i->getHolder().getSpeed()>5) return true;
    }
    return false;
}

void ConflictClass::informCars(JudgeCommand jc) {
    //std::cout << jc << "  Changed state ";
    for (auto& x: myCars){
       // std::cout << x->getID() << ", ";
        x->informDecision(jc);
    }
    //std::cout << std::endl;
}