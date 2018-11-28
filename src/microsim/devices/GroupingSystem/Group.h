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
    int nMembers, totalMembers = 0;
    Messenger* members[15];
    libsumo::TraCIColor myColor;
    void finishGroup();
    bool laneChangeInAction = false;
    ConflictClass* myCC = nullptr;
   // MSLCM_SmartSL2015* followerLeader = nullptr;
public:
    //MSLCM_SmartSL2015 *getFollowerLeader() const;
    std::vector<MSLCM_SmartSL2015*> LCFifo;
    std::vector<std::string*> carIDs;
public:
    Group(Messenger* leader);
    ~Group();
    std::string direction;
    Messenger* groupLeader;
    bool canJoin;
    void setMyCC (ConflictClass* cc);
    void addNewMember(Messenger* member);
    void removeCar(Messenger *who);
    Messenger* getFollowerOf(Messenger* who);
    Messenger* getLeaderOf(Messenger* who);
    double getGroupLength();
    int maxMembers = 8;
    //void laneChange(MSLCM_SmartSL2015* followerLeader);
    void endLaneChange();
    bool isChanging();

    int getNMembers() const;

    void laneChange(MSLCM_SmartSL2015* follower);

    Messenger** getMembers();
};


#endif //SUMO_GROUP_H
