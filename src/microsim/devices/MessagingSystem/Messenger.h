//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSENGER_H
#define SUMO_MESSENGER_H


#include <microsim/devices/GroupingSystem/Group.h>
#include <string>
#include <utils/vehicle/SUMOVehicle.h>
#include <microsim/devices/MarkerSystem/EntryMarker.h>
#include <microsim/devices/MSDevice_SAL.h>

#define MAX_DISTANCE 50

class Group;

class Messenger {
    Group* myGroup = nullptr;
    SUMOVehicle* myVehicle;
    ExitMarker* myExitMarker;

public:
    MSDevice_SAL *mySAL;
    Messenger(SUMOVehicle *myVech, MSDevice_SAL *mySAL);
    ~Messenger();
    void joinAGroup(EntryMarker &entryMarker);
    void leaveGroup();
    void needToChangeLane(int result, int offset);
    Group* getGroup();
};


#endif //SUMO_MESSENGER_H
