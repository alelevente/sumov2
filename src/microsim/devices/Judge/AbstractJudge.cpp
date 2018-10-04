//
// Created by levente on 2018.07.31..
//

#include "AbstractJudge.h"
#include "ConflictClass.h"
#include "microsim/devices/MSDevice_SAL.h"
#include <libsumo/Simulation.h>

void AbstractJudge::carPassedPONR(MSDevice_SAL *who) {
    ++cameIn;
    lastCameIn = libsumo::Simulation::getCurrentTime() / 1000;
#ifdef KILLCARS
    std::string *newCar = new std::string(who->getVehicle()->getID());
    carsIn.insert(carsIn.end(), newCar);
    lastCIChanged = libsumo::Simulation::getCurrentTime();
#endif
}

void AbstractJudge::carLeftJunction(MSDevice_SAL *who) {

#ifdef KILLCARS
    auto tobeDeleted = carsIn.begin();
    for (auto i=carsIn.begin(); i!=carsIn.end(); ++i) {
        if (*(*i) == who->getVehicle()->getID()) tobeDeleted = i;
    }
    carsIn.erase(tobeDeleted);
    lastCIChanged = libsumo::Simulation::getCurrentTime();
#endif

    int i=0;
    while (!conflictClasses[i]->hasVehicle(who) && i<conflictClasses.size()) ++i;
    if (i<conflictClasses.size()) {
        conflictClasses[i]->removeVehicle(who);
        ++wentOut;
        if (conflictClasses[i]->isEmpty() && i == activeCC) changeCC();
    }
    who->resetVehicleColor();
}

void AbstractJudge::reportComing(Group *group, const std::string &direction) {
    int which = decideCC(group, direction);
    conflictClasses[which]->joinGroup(group);
    group->setMyCC(conflictClasses[which]);
    if (conflictClasses[activeCC]->isEmpty()) changeCC();
    group->getMembers()[0]->mySAL->setVehicleColor(conflictClasses[which]->getMyColor());
}

AbstractJudge::~AbstractJudge() {}
void AbstractJudge::informCCEnded(ConflictClass *cc) {}