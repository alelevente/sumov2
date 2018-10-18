//
// Created by levente on 2018.08.26..
//

#ifndef SUMO_MDDFCONFLICTCLASS_H
#define SUMO_MDDFCONFLICTCLASS_H


#include "ConflictClass.h"

class MDDFConflictClass: public ConflictClass {

    int age = 0;
    bool badGuy=false;

public:
    virtual double calculatePrice();
    virtual bool canJoinGroup(int nMembers, const std::string& inDirection, const std::string& outDirection);
    void setLastTime(long int time);
    bool isOld();
    void setBadGuy();
    void resetBadGuy();
};


#endif //SUMO_MDDFCONFLICTCLASS_H
