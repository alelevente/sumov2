//
// Created by levente on 2018.07.21..
//
#include "LCManager.h"
#include <libsumo/Vehicle.h>
#include <microsim/devices/MessagingSystem/MessagingProxy.h>
#include <libsumo/Simulation.h>
#include <microsim/MSVehicleContainer.h>
#include <microsim/MSVehicleControl.h>


LCManager::LCManager(MSLCM_SmartSL2015 *myLC):
    myLC(myLC) {}

void LCManager::setIsMember(Group* group) {
    myLC->setMyGroupState(MEMBER);
    SUMOVehicle* holder = myLC->getMyVehicle();
    MessagingProxy::getInstance().getGroupOf(holder->getID());
    libsumo::Vehicle::setLaneChangeMode(holder->getID(), 512);
    auto carId = group->carIDs.begin();

    for (auto i = group->LCFifo.begin(); i != group->LCFifo.end(); ++i) {
        LCFifo.insert(LCFifo.end(), *i);
        carIDs.insert(carIDs.end(), *(carId++));
    }
}

void LCManager::setIsLeader() {
    myLC->setMyGroupState(LEADER);
    libsumo::Vehicle::setLaneChangeMode(myLC->getMyVehicle()->getID(), 1621);
    libsumo::Vehicle::setSpeed(myLC->getMyVehicle()->getID(), -1);
    requestedChanges = 0;
    hasChanged = 0;
}

void LCManager::leaveGroup() {
    myLC->setMyGroupState(OUT);
    groupChanged();
    std::string ID = myLC->getMyVehicle()->getID();
    libsumo::Vehicle::setLaneChangeMode(ID, 1621);

    //needed to forget previous changerequs:
    libsumo::Vehicle::setSpeed(ID, -1);
    requestedChanges = 0;
    hasChanged = 0;
}

void LCManager::groupChanging(MSLCM_SmartSL2015 *follower) {
    bool benne = false;
    for (auto i = LCFifo.begin(); i != LCFifo.end(); ++i) if ((*i) == follower) benne = true;
    if (!benne) {
        LCFifo.insert(LCFifo.end(), follower);
        carIDs.insert(carIDs.end(), new std::string(follower->getMyVehicle()->getID()));
    }
}

void LCManager::hasToChange(int direction) {
    libsumo::Vehicle::changeLaneRelative(myLC->getMyVehicle()->getID(), direction, 1000);
    myLC->setOffset(direction);
    lastDir = direction;
    ++requestedChanges;
    lastChange = libsumo::Simulation::getCurrentTime();
}

void LCManager::changed() {
    if (requestedChanges>hasChanged) ++hasChanged;
}


void LCManager::groupChanged() {
    if (myLC->myFollower != nullptr) {
        std::string ID = myLC->myFollower->getID();
        libsumo::Vehicle::setLaneChangeMode(ID, 1621);
        libsumo::Vehicle::setSpeed(ID, 15);
    }
}

void LCManager::blocker(MSLCM_SmartSL2015 *who) {
    std::string ID = who->getMyVehicle()->getID();
    libsumo::Vehicle::setSpeed(ID, 0);
    libsumo::Vehicle::setLaneChangeMode(ID, 512);
}