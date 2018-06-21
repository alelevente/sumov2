//
// Created by levente on 2018.06.20..
//

#include "MessengerSystem.h"

MessengerSystem& MessengerSystem::getInstance() {
    static MessengerSystem ms;
    return ms;
}

void MessengerSystem::addNewMessengerAgent(const std::string &id) {
    Messenger* newMessenger = new Messenger();
    messengerMap.insert(std::make_pair(id, newMessenger));
}

void MessengerSystem::removeMessengerAgent(const std::string &id) {
    Messenger* mes = messengerMap[id];
    messengerMap.erase(id);
    delete mes;
}

MessengerSystem::~MessengerSystem() {
    Messenger* mes;
    for (auto i = messengerMap.begin(); i != messengerMap.end(); ++i){
        mes = (*i).second;
        messengerMap.erase(i);
        delete mes;
    }
}