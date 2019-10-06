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
class MSDevice_SAL;

/// @brief This class is responsible for managing lane change manouvers in the simulation abstraction layer
class LCManager {
    /// @brief the smart car's lane change model
    MSLCM_SmartSL2015 *myLC;
    /// @brief First-in-First-out list of the group leaders who made possible our lane changes (pointer representation)
    std::vector<MSLCM_SmartSL2015*> LCFifo;
    /// @brief First-in-First-out list of the group leaders who made possible our lane changes (string, ID representation)
    std::vector<std::string*> carIDs;
    /// @brief number of absolved lane changes
    int hasChanged = 0;
    /// @brief number of requested lane changes
    int requestedChanges = 0;
    /// @brief direction of last requested lane change
    int lastDir = 0;
    std::string vehID;

public:
    SUMOTime lastChange = 0;
    /// @brief constructor
    LCManager(MSLCM_SmartSL2015* myLC);
    ~LCManager();
    /// @brief inform LCManager about the changes in group membership
    void setIsMember(Group* group);
    /// @brief inform LCManager if the smart car left the group
    void leaveGroup();
    /// @brief inform LCManager that the car it controls has become a group leader
    void setIsLeader();
    /// @brief infrom LCManager that a lane change is needed in the given direction
    void hasToChange(int direction);
    /// @brief updates the Fifos
    void groupChanging(MSLCM_SmartSL2015* follower);
    /// @brief called when the last car of a group has finished its lane change
    void groupChanged();
    /// @brief used to inform a group leader that it is now a blocker, so it has to let in another group
    static void blocker(MSLCM_SmartSL2015 *who, long groupID);
    /// @brief called, when the controlled car changed its change of lane
    void changed();
};


#endif //SUMO_LCMANAGER_H
