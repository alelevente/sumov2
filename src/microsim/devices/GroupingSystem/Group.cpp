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
    //if (followerLeader!= nullptr) members[nMembers-1]->mySAL->addFollower(followerLeader);
}

void Group::removeFirstCar() {
    if (nMembers == 1) {
       /* if (followerLeader != nullptr) {
            members[0]->mySAL->informStoppedToContinue(followerLeader);
        }*/
    }
    Messenger* first = members[0];
    for (int i=1; i<nMembers; ++i){
        members[i-1] = members[i];
    }
    members[nMembers-1] = nullptr;
    --nMembers;

    first->mySAL->informNoLongerLeader();
    first->mySAL->resetVehicleColor();
    first->myGroup = nullptr;

    if (nMembers == 0) finishGroup();
    else {
        members[0]->mySAL->informBecomeLeader();
        groupLeader = members[0];
    }
}

void Group::finishGroup() {
    delete this;
}

Messenger* Group::getFollowerOf(Messenger *who) {
    int i=0;
    for (i=0; members[i]!=who && i<nMembers; ++i);
    if (members[i+1] == nullptr) std::cout << who->myVehicle->getID() << " is last." << std::endl;
    return members[i+1];
}

Messenger* Group::getLeaderOf(Messenger *who) {
    int i=0;
    for (i=0; members[i+1]!=who && i<nMembers; ++i);
    return members[i];
}

double Group::getGroupLength() {
    if (nMembers == 1) return 0;//libsumo::Vehicle::getLength(members[0]->mySAL->getHolder().getID());

    libsumo::TraCIPosition pos = libsumo::Vehicle::getPosition(members[0]->mySAL->getHolder().getID());
    return libsumo::Vehicle::getDrivingDistance2D(members[nMembers-1]->mySAL->getHolder().getID(), pos.x, pos.y);
}

int Group::getNMembers() const {
    return nMembers;
}

/*void Group::laneChange(MSLCM_SmartSL2015 *followerLeader) {
    laneChangeInAction = true;
    //this->followerLeader = followerLeader;
    for (int i=0; i<nMembers; ++i) {
        members[i]->mySAL->addFollower(followerLeader);
    }
}*/

void Group::endLaneChange() {
    laneChangeInAction = false;
   // this->followerLeader = nullptr;
}

bool Group::isChanging() {
    return laneChangeInAction;
}

/*MSLCM_SmartSL2015 *Group::getFollowerLeader() const {
  //  return followerLeader;
    return nullptr;
}*/


void Group::laneChange(MSLCM_SmartSL2015 *follower) {
    bool benne = false;
    for (auto i = LCFifo.begin(); i != LCFifo.end(); ++i) if ((*i) == follower) benne = true;
    if (!benne) LCFifo.insert(LCFifo.end(), follower);
    for (int i=0; i<nMembers; ++i) {
        members[i]->mySAL->groupChanging(follower);
    }
}

Messenger** Group::getMembers() {
    return members;
}