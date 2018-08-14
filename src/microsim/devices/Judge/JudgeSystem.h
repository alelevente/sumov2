//
// Created by levente on 2018.08.08..
//

#ifndef SUMO_JUDGESYSTEM_H
#define SUMO_JUDGESYSTEM_H

#include <string>
#include <map>
#include "microsim/devices/Judge/AbstractJudge.h"

class AbstractJudge;

class JudgeSystem {
    std::map<std::string, AbstractJudge*> judgeMap;
    JudgeSystem();
    ~JudgeSystem();
    JudgeSystem(JudgeSystem const&);
    void operator=(const JudgeSystem&);

public:
    static JudgeSystem& getInstance();
    AbstractJudge* getJudgeByName(const std::string& name);
};


#endif //SUMO_JUDGESYSTEM_H
