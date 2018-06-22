//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSENGERSYSTEM_H
#define SUMO_MESSENGERSYSTEM_H


#include <map>
#include "Messenger.h"

class MessengerSystem {
    friend class MessagingProxy;
    friend class Messenger;
    MessengerSystem();
    ~MessengerSystem();
    MessengerSystem(MessengerSystem const&);
    void operator=(const MessengerSystem&);
    std::map<std::string, Messenger*> messengerMap;

public:
    static MessengerSystem& getInstance();
    void addNewMessengerAgent(const std::string &id, SUMOVehicle *myVeh, MSDevice_SAL *mySAL);
    void removeMessengerAgent(const std::string &id);
};


#endif //SUMO_MESSENGERSYSTEM_H
