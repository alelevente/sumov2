//
// Created by levente on 2018.06.21..
//

#ifndef SUMO_GROUP_H
#define SUMO_GROUP_H


#include <microsim/devices/MessagingSystem/Messenger.h>
#include <string>
#include <libsumo/TraCIDefs.h>
#include <microsim/lcmodels/MSLCM_SmartSL2015.h>
#include <microsim/devices/Judge/ConflictClass.h>

class Messenger;
class MSLCM_SmartSL2015;


/**
 * @class Group
 * @brief This class realizes the intelligent group (platoon).
 */
class Group {
    /// @brief actual number of smart cars in the group
    int nMembers = 0;
    /// @brief number of vehicles which have ever participated in the group
    int totalMembers = 0;

    /// @brief list of the current members of the group
    Messenger* members[15];

    /// @brief the groups color in the GUI
    libsumo::TraCIColor myColor;

    /// @brief called when the last member of the group has left the junction
    void finishGroup();

    /// @brief true if a lane change is in progress
    bool laneChangeInAction = false;

    /// @brief In a junction it is the pointer of the conflict class which the group is assigned for. Otherwise its nullptr.
    ConflictClass* myCC = nullptr;
public:
    /// @brief First-in-First-out list of the group leaders who made possible our group's lanechange
    std::vector<MSLCM_SmartSL2015*> LCFifo;
    /// @brief list of the actual members of the group
    std::vector<std::string*> carIDs;

    /// @brief contructor
    Group(Messenger* leader);
    /// @brief destructor
    ~Group();
    /// @brief direction parameter through an intersection in form "entry marker's name - exit marker's name"
    std::string direction;
    /// @brief pointer to the group leader's messenger representation
    Messenger* groupLeader;
    /// @brief defines if join is currently allowed
    bool canJoin;
    /// @brief setter of myCC
    void setMyCC (ConflictClass* cc);
    /// @brief adds a new member to the group
    void addNewMember(Messenger* member);
    /**
     * @brief removes a given car from the group
     * @param who the car to remove
     */
    void removeCar(Messenger *who);

    /**
     *
     * @param who The car whose follower is in the question.
     * @return Follower of the car pointed by parameter 'who' in the group.
     */
    Messenger* getFollowerOf(Messenger* who);

    /**
     *
     * @param who The car whose follower is in the question.
     * @return The car in front of the smart car, pointed by parameter 'who' in the group.
     */
    Messenger* getLeaderOf(Messenger* who);

    /// @brief returns the length of group
    double getGroupLength();

    /// @brief maximum size of a group
    int maxMembers = 12;
    /// @brief called if lane changing is finished
    void endLaneChange();
    /**
     *
     * @return true, if lane changing is in action
     */
    bool isChanging();

    /// @brief number of smart cars actually in the group
    int getNMembers() const;

    /**
     * @brief inform the next car in the group about a lane-change manuevre
     * @param follower the smart car to inform
     */
    void laneChange(MSLCM_SmartSL2015* follower);

    /// @brief getter of list of members
    Messenger** getMembers();
};


#endif //SUMO_GROUP_H
