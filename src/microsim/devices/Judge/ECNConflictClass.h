//
// Created by levente on 2019.09.17..
//

#ifndef SUMO_ECNCONFLICTCLASS_H
#define SUMO_ECNCONFLICTCLASS_H


#include "ConflictClass.h"

class ECNConflictClass: public ConflictClass {
    std::vector<std::string> directionList;
    std::vector<MSDevice_SAL*>* nextList = new std::vector<MSDevice_SAL*>();
public:
    void clearDirections();
    void addDirection(const std::string& dirName);
    bool containsDirection(const std::string& dirName);
    void setNextList(const std::vector<MSDevice_SAL*>& nextList);
    virtual void informCars(JudgeCommand jc);
    void removeAllVehicles();
    void setColor(bool toRed);
    void resetNextCars();
};


#endif //SUMO_ECNCONFLICTCLASS_H
