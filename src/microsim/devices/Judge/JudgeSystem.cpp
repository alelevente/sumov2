//
// Created by levente on 2018.08.08..
//

#include "JudgeSystem.h"
#include "RRJudge.h"
#include "MDDFJudge.h"
#include <fstream>

//#define TESTMAP
#define DEVELOPING

JudgeSystem::JudgeSystem() {
#ifdef DEVELOPING
    std::ifstream input("/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judges", std::ifstream::in);
#else
    std::ifstream input("../Configs/JudgeConfs/judges", std::ifstream::in);
#endif

    int nJudges;
    input >> nJudges;

    std::string inStr;
    for (int i=0; i<nJudges; ++i){
        std::string name, type, path;
        int posX, posY, radius, ponrRadius;
        input >> name;
        input >> type;
        input >> posX >> posY >> radius >> ponrRadius;
        input >> path;
        AbstractJudge* abstractJudge;
        if (type == "RR") {
            abstractJudge = new RRJudge(path);
            abstractJudge->posX = posX;
            abstractJudge->posY = posY;
            abstractJudge->stopRadius = radius;
            abstractJudge->ponrRadius = ponrRadius;
        } else if (type == "MDDF") {
            abstractJudge = new MDDFJudge(path);
            abstractJudge->posX = posX;
            abstractJudge->posY = posY;
            abstractJudge->stopRadius = radius;
            abstractJudge->ponrRadius = ponrRadius;
        }
        judgeMap.insert(judgeMap.end(), std::make_pair(name, abstractJudge));
    }
}

JudgeSystem& JudgeSystem::getInstance() {
    static JudgeSystem js;
    return js;
}

AbstractJudge* JudgeSystem::getJudgeByName(const std::string &name) {
    return judgeMap[name];
}

JudgeSystem::~JudgeSystem() {
    for (auto i=judgeMap.begin(); i!=judgeMap.end(); ++i){
        delete (*i).second;
    }
}

void JudgeSystem::doUpdate(const SUMOTime& now) {
    for (auto& j: judgeMap){
        if (j.second->initialized) j.second->step(now);
    }
}