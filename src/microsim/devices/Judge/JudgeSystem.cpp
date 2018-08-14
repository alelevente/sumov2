//
// Created by levente on 2018.08.08..
//

#include "JudgeSystem.h"
#include "RRJudge.h"
#include <fstream>

JudgeSystem::JudgeSystem() {
    std::ifstream input("/home/levente/Egyetem/6_felev/EFOP/TestMap/judges", std::ifstream::in);
    int nJudges;
    input >> nJudges;

    std::string inStr;
    for (int i=0; i<nJudges; ++i){
        std::string name, type, path;
        int posX, posY;
        input >> name;
        input >> type;
        input >> posX >> posY;
        input >> path;
        AbstractJudge* abstractJudge;
        if (type == "RR") {
            abstractJudge = new RRJudge(path);
            abstractJudge->posX = posX;
            abstractJudge->posY = posY;
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