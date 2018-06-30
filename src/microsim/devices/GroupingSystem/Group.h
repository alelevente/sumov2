//
// Created by levente on 2018.06.21..
//

#ifndef SUMO_GROUP_H
#define SUMO_GROUP_H


#include <microsim/devices/MessagingSystem/Messenger.h>
#include <string>
#include <libsumo/TraCIDefs.h>

class Messenger;

class Group {
    int nMembers;
    Messenger* members[15];
    libsumo::TraCIColor myColor;
    void finishGroup();

public:
    Group(Messenger* leader);
    ~Group();
    std::string direction;
    Messenger* groupLeader;
    bool canJoin;
    void addNewMember(Messenger* member);
    void removeFirstCar();
    Messenger* getFollowerOf(Messenger* who);
    int maxMembers = 15;
};


#endif //SUMO_GROUP_H
