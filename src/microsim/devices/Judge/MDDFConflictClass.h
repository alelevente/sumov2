//
// Created by levente on 2018.08.26..
//

#ifndef SUMO_MDDFCONFLICTCLASS_H
#define SUMO_MDDFCONFLICTCLASS_H


#include "ConflictClass.h"

/// @brief This class implements the corresponding conflict class for MDDF judge
class MDDFConflictClass: public ConflictClass {
    /// @brief time stamp of last activation time
    int age = 0;
    /// @brief badGuy means there only are cars which are stucked behind another CC
    bool badGuy=false;

public:
    /// @brief constructor
    MDDFConflictClass(): ConflictClass() {}
    /// @brief constructor
    MDDFConflictClass(int radius): ConflictClass(radius) {}
    /// @brief In MDDF CC calculatePrice returns the shortest remaining distance among its smart cars
    virtual double calculatePrice();
    /// @brief in MDDF CC it always returns true
    virtual bool canJoinGroup(int nMembers, const std::string& inDirection, const std::string& outDirection);
    /// @brief setter of age
    void setLastTime(long int time);
    /// @brief MDDF CC is considered to be old if more than 90s elapsed since last active state
    bool isOld();
    /// @brief setter of badGuy
    void setBadGuy();
    /// @brief setter of badGuy
    void resetBadGuy();
};


#endif //SUMO_MDDFCONFLICTCLASS_H
