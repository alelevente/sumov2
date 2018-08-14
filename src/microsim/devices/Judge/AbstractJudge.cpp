//
// Created by levente on 2018.07.31..
//

#include "AbstractJudge.h"
#include "ConflictClass.h"
#include "microsim/devices/MSDevice_SAL.h"

void AbstractJudge::carPassedPONR(MSDevice_SAL *who) {
    ++cameIn;
}

void AbstractJudge::carLeftJunction(MSDevice_SAL *who) {
    ++wentOut;
    int i=0;
    while (!conflictClasses[i]->hasVehicle(who) && i<conflictClasses.size()) ++i;
    if (i<conflictClasses.size()) {
        conflictClasses[i]->removeVehicle(who);
    }
    who->resetVehicleColor();
}

void AbstractJudge::reportComing(Group *group, const std::string &direction) {
    int which = decideCC(group, direction);
    conflictClasses[which]->joinGroup(group);
    group->getMembers()[0]->mySAL->setVehicleColor(conflictClasses[which]->getMyColor());
}

AbstractJudge::~AbstractJudge() {}
void AbstractJudge::informCCEnded(ConflictClass *cc) {}