//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSAGINGPROXY_H
#define SUMO_MESSAGINGPROXY_H

#include <string>
#include <microsim/devices/MarkerSystem/EntryMarker.h>
#include <microsim/devices/GroupingSystem/Group.h>


class MessagingProxy {
    MessagingProxy();
    ~MessagingProxy();
    MessagingProxy(MessagingProxy const&);
    void operator=(const MessagingProxy&);

public:
    static MessagingProxy& getInstance();
    void informEnterEntryMarker(const std::string& messengerID, EntryMarker* entryMarker);
    void informEnterExitMarker(const std::string& messengerID, ExitMarker* exitMarker);
    bool informLaneChange(const std::string &messengerID, MSLCM_SmartSL2015 *followerLCM, int offset);
    Group* getGroupOf(const std::string &messengerID);
    Messenger* getMessenger(const std::string& messengerID);
};


#endif //SUMO_MESSAGINGPROXY_H
