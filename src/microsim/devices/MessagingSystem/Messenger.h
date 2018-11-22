//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSENGER_H
#define SUMO_MESSENGER_H


#include <microsim/devices/GroupingSystem/Group.h>
#include <string>
#include <utils/vehicle/SUMOVehicle.h>
#include "microsim/devices/MarkerSystem/EntryMarker.h"

#include "microsim/lcmodels/MSLCM_SmartSL2015.h"
#include "microsim/devices/MarkerSystem/ExitMarker.h"

#define MAX_DISTANCE 50

class Group;
class MSDevice_SAL;
class MSLCM_SmartSL2015;

class EntryMarker;

class Messenger {
    friend class Group;
    Group* myGroup = nullptr;
    SUMOVehicle* myVehicle;
    ExitMarker* myExitMarker;

public:
    MSDevice_SAL *mySAL;
    Messenger(SUMOVehicle *myVech, MSDevice_SAL *mySAL);
    ~Messenger();
    void joinAGroup(EntryMarker &entryMarker);
    void leaveGroup();
    void needToChangeLane(MSLCM_SmartSL2015 *follower, int offset);
    Group* getGroup();
};


#endif //SUMO_MESSENGER_H
