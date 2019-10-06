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
    static long groupIDGenerator;
    myGroupID = groupIDGenerator++;
    nMembers = 1;
    members[0] = leader;
    myJudge = leader->mySAL->getMyJudge();
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
    for (auto& g: groupsWaitRequest) {
        g->informGroupLeftJunction(myGroupID);
    }
    myJudge->groupLeft(myGroupID);
}

void Group::setMyCC(ConflictClass *cc) {
    myCC = cc;
    for (auto m: members){
        if (m == nullptr) continue;
        m->mySAL->setVehicleColor(cc->getMyColor());
    }
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

    AbstractJudge* judge = first->mySAL->informNoLongerLeader();
    first->mySAL->resetVehicleColor();
    this->myCC->removeVehicle(first->mySAL);
    first->myGroup = nullptr;

    if (nMembers == 0) finishGroup(who, judge);
    else if (idx == 0){
        members[0]->mySAL->informBecomeLeader();
        groupLeader = members[0];
    } else {
        for (int j = idx; j<nMembers; ++j) {
            members[j]->mySAL->setMyLeaderMessenger(members[j-1]);
        }
    }
}

void Group::finishGroup(Messenger *who, AbstractJudge *judge) {
    std::cout << "group left: " << this << std::endl;
    who->mySAL->myLCm->groupChanged();
    judge->groupLeft(myGroupID);
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

long Group::getMyGroupID() const {
    return myGroupID;
}

void Group::informGroupLeftJunction(long groupID) {
    if (groupsForWaitFor.empty()) return;
    auto it = std::find(groupsForWaitFor.begin(), groupsForWaitFor.end(), groupID);
    if (it != groupsForWaitFor.end()) groupsForWaitFor.erase(it);
    auto it2 = groupsWaitRequest.begin();
    while (it2 != groupsWaitRequest.end()){
        if ((*it2)->getMyGroupID() == groupID) groupsWaitRequest.erase(it2);
        if (it2==groupsWaitRequest.end()) break;
        ++it2;
    }
    if (it2 != groupsWaitRequest.end()) groupsWaitRequest.erase(it2);
    if (groupsForWaitFor.empty()) {
        std::string ID = members[0]->mySAL->getVehicle()->getID();
        libsumo::Vehicle::setLaneChangeMode(ID, 1621);
    }
}

void Group::informGroupThatChanged(long groupID) {
    informGroupLeftJunction(groupID);
}

void Group::informGroupHaveToWaitFor(long groupID) {
    std::cout << myGroupID << "group have to wait for: " << groupID << std::endl;
    groupsForWaitFor.insert(groupsForWaitFor.end(), groupID);
}

void Group::informGroupIsRequester(MSDevice_SAL *waitedGroupLeader) {
    std::cout << waitedGroupLeader->getGroup() << " pushed back" << std::endl;
    groupsWaitRequest.push_back(waitedGroupLeader->getGroup());
    std::cout << waitedGroupLeader->getGroup()->getNMembers() << std::endl;
}

void Group::informGroupChanged() {
    if (groupsWaitRequest.size() == 0) return;
    std::cout << groupsWaitRequest.size() << std::endl;
    for (auto& group: groupsWaitRequest) std::cout << group << ", ";
    std::cout << std::endl;
    Group* waiter = groupsWaitRequest[0];
    waiter->informGroupThatChanged(myGroupID);
    std::cout << waiter << " informed " << std::endl;
    if (groupsWaitRequest.size() == 0) return;
    if (groupsWaitRequest.size() != 1){
        groupsWaitRequest.erase(groupsWaitRequest.begin());
    } else {
        groupsWaitRequest.clear();
    }
}
