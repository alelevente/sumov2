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
    //libsumo::Vehicle::setLaneChangeMode(holder->getID(), 0);
    auto carId = group->carIDs.begin();

    for (auto i = group->LCFifo.begin(); i != group->LCFifo.end(); ++i) {
        LCFifo.insert(LCFifo.end(), *i);
        carIDs.insert(carIDs.end(), *(carId++));
    }
}

void LCManager::setIsLeader() {
    myLC->setMyGroupState(LEADER);
    //libsumo::Vehicle::changeLaneRelative(myLC->getMyVehicle()->getID(), 0, 0);
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
    //std::cout << ID << ": will continue" << std::endl;
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
    //std::cout << myLC->getMyVehicle()->getID() << " has to change: " << direction << std::endl;
    libsumo::Vehicle::changeLaneRelative(myLC->getMyVehicle()->getID(), direction, 1000);
    //libsumo::Vehicle::changeSublane(myLC->getMyVehicle()->getID(), direction*2.75);
    myLC->setOffset(direction);
    lastDir = direction;
    ++requestedChanges;
    lastChange = libsumo::Simulation::getCurrentTime();
}

void LCManager::changed() {
    if (requestedChanges>hasChanged) ++hasChanged;
    //myLC->lineUpForCenterOfLane();
}

void LCManager::synch() {
    //std::cout << libsumo::Simulation::getCurrentTime()-lastChange << std::endl;
    if (libsumo::Simulation::getCurrentTime()-lastChange > 3500) {
        //std::cout << myLC->getMyVehicle()->getID() << ": has resent the request of " << lastDir << std::endl;
       /* if (myLC->getMyVehicle()->isSelected()) std::cout <<
                                                          myLC->getMyVehicle()->getID() <<": " << hasChanged << "/" << requestedChanges << std::endl;*/
        if ((hasChanged != requestedChanges) && (lastDir!=0)) {
        // ->    libsumo::Vehicle::changeLaneRelative(myLC->getMyVehicle()->getID(), lastDir, 0);
            //libsumo::Vehicle::changeSublane(myLC->getMyVehicle()->getID(), lastDir*2.75);
          //  std::cout << myLC->getMyVehicle()->getID() << "is reset" << std::endl;
        }
        lastChange = libsumo::Simulation::getCurrentTime();
    }
}


void LCManager::groupChanged() {
    /*if (LCFifo.size() != 0 && carIDs.size() != 0) {
        //MSVehicleControl::loadedVehBegin()
        //std::vector<std::string> ids = libsumo::Vehicle::getIDList();

        MSVehicleControl& vc = MSNet::getInstance()->getVehicleControl();
        bool benne = vc.getVehicle(*carIDs[0]) != 0;
       /* for (auto x= vc.loadedVehBegin(); x!=vc.loadedVehEnd() && !benne; ++x) {
            if ((*x).first == *carIDs[0]) benne = true;
        }*/
       /* if (!benne) {

            delete *carIDs.begin();LCFifo.erase(LCFifo.begin());
            carIDs.erase(carIDs.begin());
            return;
        }*/
        //std::cout << myLC->getMyVehicle()->getID() << " has FIFO of: ";
        // for (auto i = LCFifo.begin(); i != LCFifo.end(); ++i)
         //   std::cout << (*i)->getMyVehicle()->getID();
        //std::cout << std::endl;
      /*  std::string ID = LCFifo[0]->getMyVehicle()->getID();
        libsumo::Vehicle::setLaneChangeMode(ID, 1621);
        libsumo::Vehicle::setSpeed(ID, -1);*/
        //libsumo::Vehicle::changeLaneRelative(ID, 0, 1);
        //std::cout << ID << ": may continue" << std::endl;

     /*   delete *carIDs.begin();LCFifo.erase(LCFifo.begin());
        carIDs.erase(carIDs.begin());
    }*/

   // std::cout << MSNet::getInstance()->getVehicleControl().getRunningVehicleNo();

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
    //libsumo::Vehicle::changeLaneRelative(ID, 0, 60000);
    //std::cout << who->getMyVehicle()->getID() << ": is blocker" << std::endl;
}