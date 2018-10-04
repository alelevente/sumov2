//
// Created by levente on 2018.08.26..
//

#ifndef SUMO_MDDFCONFLICTCLASS_H
#define SUMO_MDDFCONFLICTCLASS_H


#include "ConflictClass.h"

class MDDFConflictClass: public ConflictClass {

    int age = 0;

public:
    double calculatePrice();
    virtual bool canJoinGroup(int nMembers, const std::string& inDirection, const std::string& outDirection);
    bool isFirst();
    void makeOlder();
};


#endif //SUMO_MDDFCONFLICTCLASS_H
