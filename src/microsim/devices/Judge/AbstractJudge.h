//
// Created by levente on 2018.07.31..
//

#ifndef SUMO_ABSTRACTJUDGE_H
#define SUMO_ABSTRACTJUDGE_H

#include <string>
#include <vector>

#define REPORT_DISTANCE 100
#define STOP_DISTANCE 20


class MSDevice_SAL;
class Group;
class ConflictClass;

class AbstractJudge {
protected:
    std::vector<ConflictClass*> conflictClasses;
    virtual int decideCC(Group *group, const std::string &direction) = 0;
    virtual void changeCC() =0;
    int activeCC = -1;
    int cameIn = 0, wentOut = 0;
    long int lastCameIn = 0, lastCheck = 0;
    std::vector<MSDevice_SAL*> carsIn;
    void makeKill();

#ifdef KILLCARS
    std::vector <std::string*> carsIn;
#endif
    long int lastCIChanged;


public:
    double posX, posY, stopRadius = 15, ponrRadius = 5;
    virtual void informCCEnded(ConflictClass* cc);
    virtual bool canPass(MSDevice_SAL* who)=0;
    virtual void carPassedPONR(MSDevice_SAL* who);
    virtual void carLeftJunction(MSDevice_SAL* who, bool byForce = false);
    virtual void reportComing(Group *group, const std::string &direction);
    virtual ~AbstractJudge();
};


#endif //SUMO_ABSTRACTJUDGE_H
