//
// Created by levente on 2018.08.01..
//

#ifndef SUMO_RRJUDGE_H
#define SUMO_RRJUDGE_H

#include "microsim/devices/Judge/AbstractJudge.h"
#include "ConflictClass.h"
#include <vector>
#include <string>

class Group;
class MSDevice_SAL;

struct ProgramElement {
    std::vector<bool> passeable;
    int duration;
};

class RRJudge: public AbstractJudge {
    virtual int decideCC(Group *group, const std::string &direction);
    std::vector<ProgramElement*> programElements;
    std::vector<std::string*> directions;
    int actualElement = 0, startTime = 0;
    int nDirs = 0, nPrograms = 0;

    virtual void changeCC();

public:
    RRJudge(const std::string& path);
    ~RRJudge();
    bool canPass(MSDevice_SAL* who);
};


#endif //SUMO_RRJUDGE_H
