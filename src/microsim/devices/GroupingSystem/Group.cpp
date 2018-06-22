//
// Created by levente on 2018.06.21..
//

#include <microsim/devices/Others/Helper.h>
#include "Group.h"


Group::Group(Messenger *leader)
{
    nMembers = 1;
    members[0] = leader;
    canJoin = true;
    myColor.a = 255;
    myColor.r = rand() % 256;
    myColor.g = rand() % 256;
    myColor.b = rand() % 256;
    members[0]->mySAL->setVehicleColor(myColor);
    members[0]->mySAL->informBecomeLeader();
}

Group::~Group() {}

void Group::addNewMember(Messenger *member) {
    if (!canJoin) throw OutOfBoundsException();
    members[nMembers++] = member;
    if (nMembers > maxMembers) canJoin = false;
    member->mySAL->setVehicleColor(myColor);
    members[nMembers-1]->mySAL->informBecomeMember();
}

void Group::removeFirstCar() {
    Messenger* first = members[0];
    for (int i=1; i<nMembers; ++i){
        members[i-1] = members[i];
    }
    --nMembers;
    first->mySAL->informNoLongerLeader();
    first->mySAL->resetVehicleColor();
    members[0]->mySAL->informBecomeLeader();
    if (nMembers == 0) finishGroup();
}

void Group::finishGroup() {
    delete this;
}