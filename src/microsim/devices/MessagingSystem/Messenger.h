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

/// @brief Messenger is a concept for modeling intelligent agents in further developments. Currently its advantages are not used.
class Messenger {
    friend class Group;

    /// @brief pointer to a smart car's group
    Group* myGroup = nullptr;
    /// @brief pointer to the smart car's vehicle itself
    SUMOVehicle* myVehicle;
    /// @brief pointer to the upcoming exit marker
    ExitMarker* myExitMarker;

    double _get_distance(const Messenger& otherAgent);

public:
    /// @brief pointer to the simulation abstraction device
    MSDevice_SAL *mySAL;
    /// @brief constructor
    Messenger(SUMOVehicle *myVech, MSDevice_SAL *mySAL);
    /// @brief destructor
    ~Messenger();
    /// @brief atomic action to join a group at the given entry marker
    void joinAGroup(EntryMarker &entryMarker);
    /// @brief atomic action to leave a group
    void leaveGroup();
    /// @brief atomic action if lane change is needed
    void needToChangeLane(MSLCM_SmartSL2015 *follower, int offset);
    Group* getGroup();
};


#endif //SUMO_MESSENGER_H
