//
// Created by levente on 2018.08.08..
//

#include "JudgeSystem.h"
#include "RRJudge.h"
#include "MDDFJudge.h"
#include "ECNJudge.h"
#include <fstream>

//#define TESTMAP
#define DEVELOPING
#define ECN

JudgeSystem::JudgeSystem() {
#ifdef DEVELOPING
    std::ifstream input("/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judges", std::ifstream::in);
#else
    std::ifstream input("../Configs/JudgeConfs/judges", std::ifstream::in);
#endif
#ifdef ECN
    ECNJudge* bah, *jaghegy, *villanyiBorsi;
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
        } else if (type == "ECN") {
            abstractJudge = new ECNJudge(path);
            abstractJudge->posX = posX;
            abstractJudge->posY = posY;
            abstractJudge->stopRadius = radius;
            abstractJudge->ponrRadius = ponrRadius;
#ifdef ECN
            if (path == "/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judgeConfs/BAH.ecnconf")
                bah = (ECNJudge*) abstractJudge;
            if (path == "/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judgeConfs/JagHegy.ecnconf")
                jaghegy = (ECNJudge*) abstractJudge;
            if (path == "/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judgeConfs/VillanyiBudaorsi.ecnconf")
                villanyiBorsi = (ECNJudge*) abstractJudge;
#endif
        }
        judgeMap.insert(judgeMap.end(), std::make_pair(name, abstractJudge));
    }
#ifdef ECN
    bah->addNeighbourPort(jaghegy, "STOP_JaghegyH1.0");
    bah->addNeighbourPort(villanyiBorsi, "STOP_BudVillV1");
    villanyiBorsi->addNeighbourPort(bah, "STOP_BAHVill");
    jaghegy->addNeighbourPort(bah, "STOP_BAHh2");
#endif
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
        delete ((*i).second);
    }
}

void JudgeSystem::doUpdate(const SUMOTime& now) {
    for (auto& j: judgeMap){
        if (j.second->initialized) j.second->step(now);
    }
}

void JudgeSystem::informJudges(void *message) {
    for (auto& jp: judgeMap){
        jp.second->informJudge(message);
    }
    delete message;
}