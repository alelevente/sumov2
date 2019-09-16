//
// Created by levente on 2018.06.21..
//

#include <microsim/devices/Others/Helper.h>
#include <libsumo/Simulation.h>
#include <libsumo/Vehicle.h>
#include "Group.h"


Group::Group(Messenger *leader):
    groupLeader(leader)
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
    for (int i=1; i<15; ++i) members[i] = nullptr;
}

Group::~Group() {
}

void Group::setMyCC(ConflictClass *cc) {
    myCC = cc;
}

void Group::addNewMember(Messenger *member) {
    if (!canJoin) {
        std::cerr << "addNewMember function: out of bounds exception." << std::endl;
        throw OutOfBoundsException();
    }
    if (member->myVehicle->isSelected()){
        std::cout << std::endl;
    }
    members[nMembers++] = member;
    ++totalMembers;
    if (totalMembers >= maxMembers) canJoin = false;
    member->mySAL->setVehicleColor(myColor);
    members[nMembers-1]->mySAL->informBecomeMember(this);
    if (myCC != nullptr) myCC->addVehicle(member->mySAL);
}

void Group::removeCar(Messenger *who) {
    int idx = 0;
    while (members[idx] != who && idx < nMembers) ++idx;
    Messenger* first = members[idx];
    for (int i=idx+1; i<nMembers; ++i){
        members[i-1] = members[i];
    }
    members[nMembers-1] = nullptr;
    --nMembers;

    first->mySAL->informNoLongerLeader();
    first->mySAL->resetVehicleColor();
    this->myCC->removeVehicle(first->mySAL);
    first->myGroup = nullptr;

    if (nMembers == 0) finishGroup(who);
    else if (idx == 0){
        members[0]->mySAL->informBecomeLeader();
        groupLeader = members[0];
    } else {
        for (int j = idx; j<nMembers; ++j) {
            members[j]->mySAL->setMyLeaderMessenger(members[j-1]);
        }
    }
}

void Group::finishGroup(Messenger *who) {
    who->mySAL->myLCm->groupChanged();
    delete this;
}

Messenger* Group::getFollowerOf(Messenger *who) {
    int i=0;
    for (i=0; members[i]!=who && i<nMembers; ++i);
    return members[i+1];
}

Messenger* Group::getLeaderOf(Messenger *who) {
    int i=0;
    for (i=0; members[i+1]!=who && i<nMembers; ++i);
    return members[i];
}

double Group::getGroupLength() {
    if (nMembers == 1) return 0;

    Position pos1 = members[0]->mySAL->getHolder().getPosition(0),
         pos2 = members[nMembers-1]->mySAL->getHolder().getPosition(0);
    return sqrt(pow(pos1.x()-pos2.x(),2) + pow(pos1.y()-pos2.y(),2));

}

int Group::getNMembers() const {
    return nMembers;
}


void Group::endLaneChange() {
    laneChangeInAction = false;
}

bool Group::isChanging() {
    return laneChangeInAction;
}



void Group::laneChange(MSLCM_SmartSL2015 *follower) {
    bool benne = false;
    for (auto i = LCFifo.begin(); i != LCFifo.end(); ++i) if ((*i) == follower) benne = true;
    if (!benne){
        LCFifo.insert(LCFifo.end(), follower);
        carIDs.insert(carIDs.end(), new std::string(follower->getMyVehicle()->getID()));
    }
    for (int i=0; i<nMembers; ++i) {
        members[i]->mySAL->groupChanging(follower);
    }
}

Messenger** Group::getMembers() {
    return members;
}