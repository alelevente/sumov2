//
// Created by levente on 2018.07.31..
//


#include "ConflictClass.h"
#include "microsim/devices/MessagingSystem/Messenger.h"
#include <libsumo/Vehicle.h>

ConflictClass::ConflictClass() {
    myColor.a = 255;
    myColor.r = rand() % 256;
    myColor.g = rand() % 256;
    myColor.b = rand() % 256;
}

const libsumo::TraCIColor& ConflictClass::getMyColor() {
    return myColor;
}

void ConflictClass::joinGroup(Group *group) {
    Messenger** msgs = group->getMembers();
   // std::cout << "Group join: ";
    for (int i=0; i<group->getNMembers(); ++i) {
        //myCars.insert(myCars.end(), msgs[i]->mySAL);
        //std::cout << msgs[i]->mySAL->getID() << " ";
        addVehicle(msgs[i]->mySAL);
    }
   // std::cout << std::endl;
}
void ConflictClass::addVehicle(MSDevice_SAL *sal) {
    if (!hasVehicle(sal)) {
        myCars.insert(myCars.end(), sal);
        //std::cout << "Single car join: " << sal->getID();
        sal->setVehicleColor(myColor);
    }
}

void ConflictClass::removeVehicle(MSDevice_SAL *sal) {
    auto i = myCars.begin();
    //for (i=myCars.begin(); *i != sal && i != myCars.end(); ++i);
    while (*i != sal && i != myCars.end()) ++i;
    if (*i == sal) {
        *i = nullptr;
        myCars.erase(i);
    }
}

bool ConflictClass::hasVehicle(MSDevice_SAL *vehicle) {
    auto i = myCars.begin();
    for (i=myCars.begin(); i != myCars.end() && *i != vehicle ; ++i);
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

bool ConflictClass::isThereCarInDanger(double x, double y) {
    for (auto i: myCars) {
        if (libsumo::Vehicle::getDrivingDistance2D((*i).getHolder().getID(), x, y) < IN_DANGER &&
                i->getHolder().getSpeed()>5) return true;
    }
    return false;
}