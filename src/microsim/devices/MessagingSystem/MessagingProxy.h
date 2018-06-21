//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MESSAGINGPROXY_H
#define SUMO_MESSAGINGPROXY_H

#include <string>
#include <microsim/devices/MarkerSystem/EntryMarker.h>


class MessagingProxy {
    MessagingProxy();
    ~MessagingProxy();
    MessagingProxy(MessagingProxy const&);
    void operator=(const MessagingProxy&);

public:
    static MessagingProxy& getInstance();
    void informEnterEntryMarker(const std::string& messengerID, EntryMarker* entryMarker);
};


#endif //SUMO_MESSAGINGPROXY_H
