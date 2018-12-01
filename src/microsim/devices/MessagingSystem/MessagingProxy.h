//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSAGINGPROXY_H
#define SUMO_MESSAGINGPROXY_H

#include <string>
#include <microsim/devices/MarkerSystem/EntryMarker.h>
#include <microsim/devices/GroupingSystem/Group.h>

/// @brief For further development singleton type MessagingProxy makes it possible to do composed manouvers and actions.
class MessagingProxy {
    //as a singleton, the following methods are private:
    MessagingProxy();
    ~MessagingProxy();
    MessagingProxy(MessagingProxy const&);
    void operator=(const MessagingProxy&);

public:
    /// @brief for access singleton class MessagingProxy
    static MessagingProxy& getInstance();
    /// @brief action list for smart cars if entering an entry marker
    void informEnterEntryMarker(const std::string& messengerID, EntryMarker* entryMarker);
    /// @brief action list for smart cars if entering an exit marker
    void informEnterExitMarker(const std::string& messengerID, ExitMarker* exitMarker);
    /// @brief action list for smart cars if there is a lane change action in progress
    bool informLaneChange(const std::string &messengerID, MSLCM_SmartSL2015 *followerLCM, int offset);

    /**
     * @brief query of a smart car's group
     * @param messengerID the ID of the smart car
     * @return pointer to the group in which the smart car is
     */
    Group* getGroupOf(const std::string &messengerID);
    /// @brief returns a the pointer to the Messenger representation of a given ID string
    Messenger* getMessenger(const std::string& messengerID);
};


#endif //SUMO_MESSAGINGPROXY_H
