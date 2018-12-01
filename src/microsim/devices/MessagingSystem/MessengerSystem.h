//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSENGERSYSTEM_H
#define SUMO_MESSENGERSYSTEM_H


#include <map>
#include "Messenger.h"


/// @brief Singleton class responsible for managing the messenger system.
class MessengerSystem {
    friend class MessagingProxy;
    friend class Messenger;
    //to be singleton, to following are private:
    MessengerSystem();
    ~MessengerSystem();
    MessengerSystem(MessengerSystem const&);
    void operator=(const MessengerSystem&);

    /// @brief list of messenger entites
    std::map<std::string, Messenger*> messengerMap;

public:
    /// @brief for accessing this singleton class
    static MessengerSystem& getInstance();
    /**
     * @brief This method is called when a new intelligent agent was created (eg. a smart car)
     * @param id ID of the new agent
     * @param myVeh Vehicle of the new agent
     * @param mySAL Simulation Abstraction Device of the new agent
     */
    void addNewMessengerAgent(const std::string &id, SUMOVehicle *myVeh, MSDevice_SAL *mySAL);
    /// @brief removes an intelligent agent's messenger interpretation which is given by its ID
    void removeMessengerAgent(const std::string &id);
};


#endif //SUMO_MESSENGERSYSTEM_H
