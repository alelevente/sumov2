//
// Created by levente on 2019.09.17..
//

#include "ECNConflictClass.h"
#include "microsim/devices/MSDevice_SAL.h"
#include <algorithm>

void ECNConflictClass::setColor(bool toRed) {
    myColor.r = toRed? 200: 0;
    myColor.g = toRed? 0: 200;
    myColor.b = 0;
}

void ECNConflictClass::addDirection(const std::string &dirName) {
    directionList.insert(directionList.end(), dirName);
}

bool ECNConflictClass::containsDirection(const std::string &dirName) {
    return std::find(directionList.begin(), directionList.end(), dirName) != directionList.end();
}

void ECNConflictClass::setNextList(const std::vector<MSDevice_SAL *> &nextList) {
    delete this->nextList;
    this->nextList = new std::vector<MSDevice_SAL*>(nextList);
}

void ECNConflictClass::informCars(JudgeCommand jc) {
    for (auto& x: myCars){
        if (nextList->empty() || std::find(nextList->begin(), nextList->end(), x) == nextList->end())
            x->informDecision(jc);
    }
}

void ECNConflictClass::clearDirections() {
    directionList.clear();
}

void ECNConflictClass::removeAllVehicles() {
    for (auto& car: myCars){
        this->removeVehicle(car);
    }
}

void ECNConflictClass::resetNextCars() {
    nextList->clear();
}

bool ECNConflictClass::isCarFirst() {
    bool front = false;
    for (auto& c: myCars){
        front = c->getVehicle()->isFrontOnLane(c->getVehicle()->getLane());
        if (front) return front;
    }
    return front;
}