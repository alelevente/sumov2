//
// Created by levente on 2018.07.31..
//

#include "AbstractJudge.h"
#include "ConflictClass.h"
#include "microsim/devices/MSDevice_SAL.h"
#include <libsumo/Simulation.h>
#include <microsim/devices/MessagingSystem/MessagingProxy.h>
#include <libsumo/Vehicle.h>
#include <microsim/MSVehicleControl.h>

void AbstractJudge::carPassedPONR(MSDevice_SAL *who) {
    ++cameIn;
    lastCameIn = libsumo::Simulation::getCurrentTime() / 1000;
    for (auto x: carsIn) if (x == who) return;
    carsIn.insert(carsIn.end(), who);
#ifdef KILLCARS
    std::string *newCar = new std::string(who->getVehicle()->getID());
    carsIn.insert(carsIn.end(), newCar);
    lastCIChanged = libsumo::Simulation::getCurrentTime();
#endif
}

void AbstractJudge::carLeftJunction(MSDevice_SAL *who, bool byForce) {

#ifdef KILLCARS
    auto tobeDeleted = carsIn.begin();
    for (auto i=carsIn.begin(); i!=carsIn.end(); ++i) {
        if (*(*i) == who->getVehicle()->getID()) tobeDeleted = i;
    }
    carsIn.erase(tobeDeleted);
    lastCIChanged = libsumo::Simulation::getCurrentTime();
#endif

    std::vector<int> where;
    int idx=0;
    auto car = carsIn.begin();
    for (auto car = carsIn.begin(); car != carsIn.end(); ++car){
        if ((*car) == who) {
            where.insert(where.end(), idx);
        }
        ++idx;
    }

    car = carsIn.begin();
    if (!byForce) for (auto ii: where) carsIn.erase(car+ii);
    //if (!byForce) carsIn.erase(car);

    int i=0;
    while (!conflictClasses[i]->hasVehicle(who) && i<conflictClasses.size()) ++i;
    if (i<conflictClasses.size()) {
        conflictClasses[i]->removeVehicle(who);
        ++wentOut;
        if (conflictClasses[i]->isEmpty() && i == activeCC) changeCC();
    }
    who->resetVehicleColor();
   std::cout << who->getID() << " has left junction ";
    if (byForce) std::cout << "by force";
    std::cout << std::endl;

}

void AbstractJudge::reportComing(Group *group, const std::string &direction) {
    int which = decideCC(group, direction);
    conflictClasses[which]->joinGroup(group);
    group->setMyCC(conflictClasses[which]);
    if (conflictClasses[activeCC]->isEmpty()) changeCC();
    group->getMembers()[0]->mySAL->setVehicleColor(conflictClasses[which]->getMyColor());
}

void AbstractJudge::makeKill() {
    //search for stucked cars in junction:
    for (auto x: carsIn) {
        if (x->locked) return;
        if ((*x).getVehicle()->getSpeed() <= 0.0001) {
            std::string carID = (*x).getVehicle()->getID();
            std::cout << (*x).getID() << std::endl;
            MessagingProxy::getInstance().informEnterExitMarker((*x).getVehicle()->getID(),
                                                                (ExitMarker*)(MarkerSystem::getInstance().findMarkerByID((*x).getVehicle()->getEdge()->getID())));
            std::cerr << (*x).getVehicle()->getID() << " has been killed" << std::endl;
            if (x->getVehicle()->getID()=="carflow14.11") {
                std::cout << "na, most";
            }
            carLeftJunction(x, true);
            //MSVehicleControl::deleteVehicle(x->getVehicle(), true);
            std::vector<int> where;
            int idx=0;
            auto car = carsIn.begin();
            for (auto car = carsIn.begin(); car != carsIn.end(); ++car){
                if ((*car) == x) {
                    where.insert(where.end(), idx);
                }
                ++idx;
            }

            car = carsIn.begin();
            for (auto ii: where) carsIn.erase(car+ii);


            libsumo::Vehicle::remove(carID, REMOVE_VAPORIZED);
            for (auto x: carsIn) std::cout << " " << x->getID();
            std::cout << std::endl;
            return;
        }
    }
}

AbstractJudge::~AbstractJudge() {}
void AbstractJudge::informCCEnded(ConflictClass *cc) {}