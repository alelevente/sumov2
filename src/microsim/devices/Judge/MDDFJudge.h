//
// Created by levente on 2018.08.26..
//

#ifndef SUMO_MDDFJUDGE_H
#define SUMO_MDDFJUDGE_H


#include <microsim/devices/GroupingSystem/Group.h>
#include "RRJudge.h"

class MDDFJudge: public AbstractJudge {
    virtual int decideCC(Group *group, const std::string &direction);
    std::vector<std::string*> directions;
    int actualElement = 0, startTime = 0;
    int nDirs = 0, nPrograms = 0;
    std::vector<ProgramElement*> programElements;

    virtual void changeCC();
    int selectNextCC();

    bool yellow = false;
    int nextActiveCC = 0, flaggedAt = 0;
    int lastRR=0;

    //calculation of change is not necesarry, if there are smart cars only in one CC or there are no cars present
    bool changeNeeded();

public:
    MDDFJudge(const std::string& path);
    ~MDDFJudge();
    bool canPass(MSDevice_SAL* who);
};


#endif //SUMO_MDDFJUDGE_H
