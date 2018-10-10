//
// Created by levente on 2018.07.21..
//

#ifndef SUMO_LCMANAGER_H
#define SUMO_LCMANAGER_H


#include <microsim/MSVehicle.h>
#include <microsim/lcmodels/MSLCM_SmartSL2015.h>
#include <microsim/devices/GroupingSystem/Group.h>

class MSLCM_SmartSL2015;
class Group;

class LCManager {
    MSLCM_SmartSL2015* letUsIn = nullptr, *myLC;
    std::vector<MSLCM_SmartSL2015*> LCFifo;
    std::vector<std::string*> carIDs;
    int lastDir = 0, hasChanged = 0, requestedChanges = 0;
    SUMOTime  lastChange = 0;
public:
    LCManager(MSLCM_SmartSL2015* myLC);
    void setIsMember(Group* group);
    void leaveGroup();
    void setIsLeader();
    void hasToChange(int direction);
    void groupChanging(MSLCM_SmartSL2015* follower);
    void groupChanged();
    static void blocker(MSLCM_SmartSL2015* who);
    void changed();
    void synch();
};


#endif //SUMO_LCMANAGER_H
