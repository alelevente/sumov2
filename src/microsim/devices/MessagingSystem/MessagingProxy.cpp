//
// Created by levente on 2018.06.20..
//

#include "MessagingProxy.h"

MessagingProxy& MessagingProxy::getInstance() {
    static MessagingProxy mp;
    return mp;
}