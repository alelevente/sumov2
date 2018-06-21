//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSENGERSYSTEM_H
#define SUMO_MESSENGERSYSTEM_H


#include <map>
#include "Messenger.h"

class MessengerSystem {
    MessengerSystem();
    ~MessengerSystem();
    MessengerSystem(MessengerSystem const&);
    void operator=(const MessengerSystem&);
    std::map<std::string, Messenger*> messengerMap;

public:
    static MessengerSystem& getInstance();
    void addNewMessengerAgent(const std::string &id);
    void removeMessengerAgent(const std::string &id);
};


#endif //SUMO_MESSENGERSYSTEM_H
