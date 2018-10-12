//
// Created by levente on 2018.08.26..
//


#include "MDDFConflictClass.h"
#include "microsim/devices/MSDevice_SAL.h"
#include "libsumo/Vehicle.h"
#include "libsumo/Simulation.h"

inline double destinationDistance(SUMOVehicle* actualCar){
    std::string myString;
    if (actualCar == nullptr || !(actualCar->hasValidRoute(myString, 0))) {
    if (actualCar != nullptr) {
            libsumo::Vehicle::remove(actualCar->getID());
        }
        return 100000000;
    }
    return libsumo::Vehicle::getDrivingDistance(actualCar->getID(), actualCar->getRoute().getLastEdge()->getID(),
                                                actualCar->getRoute().getLastEdge()->getLength(),0);
}

double MDDFConflictClass::calculatePrice() {
    if (myCars.size() == 0) return -1;
    MSDevice_SAL* actualCar;
    actualCar = myCars[0];


    double min = destinationDistance(actualCar->getVehicle());
    double x;
    for (auto i=myCars.begin(); i!=myCars.end(); ++i) {
        x = destinationDistance((*i)->getVehicle());
        if (min > x) min = x;
    }

    return min;
    return badGuy? min*min: min;
}

bool MDDFConflictClass::canJoinGroup(int nMembers, const std::string &inDirection, const std::string &outDirection) {
    return true;
}

bool MDDFConflictClass::isFirst() {
    for (auto x: myCars)
    {
        if (x->isFirst()) return true;
    }
    return false;
}

void MDDFConflictClass::setLastTime(long int time) {
    age = time;
}

bool MDDFConflictClass::isOld() {
    return (libsumo::Simulation::getCurrentTime()/1000 - age) > 90;
}

void MDDFConflictClass::setBadGuy() {
    badGuy = true;
}

void MDDFConflictClass::resetBadGuy() {
    badGuy = false;
}