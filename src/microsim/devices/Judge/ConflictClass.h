//
// Created by levente on 2018.07.31..
//

#ifndef SUMO_CONFLICTCLASS_H
#define SUMO_CONFLICTCLASS_H


#include <vector>
#include <libsumo/TraCIDefs.h>


#define MAX_CC_MEMBERS 10

class MSDevice_SAL;
class Group;

class ConflictClass {
    friend class RRJudge;
    libsumo::TraCIColor myColor;
protected:
    std::vector<MSDevice_SAL*> myCars;

public:
    ConflictClass();
    virtual double calculatePrice();
    const libsumo::TraCIColor& getMyColor();
    virtual bool canJoinGroup(int nMembers, const std::string& inDirection, const std::string& outDirection);
    virtual void joinGroup(Group* group);
    virtual void removeVehicle(MSDevice_SAL* sal);
    bool hasVehicle(MSDevice_SAL* vehicle);
};


#endif //SUMO_CONFLICTCLASS_H
