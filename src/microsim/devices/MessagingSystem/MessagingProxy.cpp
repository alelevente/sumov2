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