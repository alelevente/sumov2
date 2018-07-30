//
// Created by levente on 2018.06.20..
//

#include "MessagingProxy.h"
#include "MessengerSystem.h"

MessagingProxy::MessagingProxy() {}
MessagingProxy::~MessagingProxy() {}

MessagingProxy& MessagingProxy::getInstance() {
    static MessagingProxy mp;
    return mp;
}

void MessagingProxy::informEnterEntryMarker(const std::string &messengerID, EntryMarker *entryMarker) {
    std::string junctionName = MarkerSystem::getJunctionName(entryMarker->getMarkerID());
    MessengerSystem::getInstance().messengerMap[messengerID]->joinAGroup(*entryMarker);
}

void MessagingProxy::informEnterExitMarker(const std::string &messengerID, ExitMarker *exitMarker) {
    MessengerSystem::getInstance().messengerMap[messengerID]->leaveGroup();
}

bool MessagingProxy::informLaneChange(const std::string &messengerID, MSLCM_SmartSL2015 *followerLCM, int offset) {
    Group* destGroup = MessengerSystem::getInstance().messengerMap[messengerID]->
            getGroup();
    if (destGroup == nullptr)
        return false;
    Messenger* follower = destGroup->getFollowerOf(MessengerSystem::getInstance().messengerMap[messengerID]);
    if (follower!= nullptr) follower->needToChangeLane(followerLCM, offset);
    return follower == nullptr;
}

Group* MessagingProxy::getGroupOf(const std::string &messengerID) {
    return MessengerSystem::getInstance().messengerMap[messengerID]->getGroup();
}

Messenger* MessagingProxy::getMessenger(const std::string &messengerID) {
    return MessengerSystem::getInstance().messengerMap[messengerID];
}