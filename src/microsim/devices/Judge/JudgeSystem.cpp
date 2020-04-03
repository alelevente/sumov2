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
//#define PAPER
//#define DIAGONAL


JudgeSystem::JudgeSystem() {
#ifdef DEVELOPING
    std::ifstream input("/home/levente/Egyetem/7_felev/szakdoga/beadas/Configs/JudgeConfs/judges", std::ifstream::in);
    //std::ifstream input("/home/levente/Egyetem/9_felev/cikkek/ifac/network/judges", std::ifstream::in);
    //std::ifstream input("/home/levente/Egyetem/9_felev/cikkek/ifac/network/judges_diag", std::ifstream::in);
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
#ifdef PAPER
    ECNJudge* A1 = (ECNJudge*)judgeMap["A1"];
    ECNJudge* A2 = (ECNJudge*)judgeMap["A2"];
    ECNJudge* A3 = (ECNJudge*)judgeMap["A3"];
    ECNJudge* A4 = (ECNJudge*)judgeMap["A4"];
    ECNJudge* A6 = (ECNJudge*)judgeMap["A6"];
    ECNJudge* A5 = (ECNJudge*)judgeMap["A5"];
    ECNJudge* A8 = (ECNJudge*)judgeMap["A8"];
    ECNJudge* A9 = (ECNJudge*)judgeMap["A9"];

    A1->addNeighbourPort(A2, "STOP_A2_nyugat");
    A1->addNeighbourPort(A3, "STOP_A3_eszaknyugat");
    A1->addNeighbourPort(A8, "STOP_A8_eszak");

    A2->addNeighbourPort(A9, "STOP_A2_eszak");
    A2->addNeighbourPort(A4, "STOP_A4_eszakkelet");
    A2->addNeighbourPort(A1, "STOP_A1_kelet");

    A8->addNeighbourPort(A1, "STOP_A1_del");
    A8->addNeighbourPort(A6, "STOP_A3_delnyugat");
    A8->addNeighbourPort(A9, "STOP_A9_nyugat");

    A9->addNeighbourPort(A8, "STOP_A8_kelet");
    A9->addNeighbourPort(A5, "STOP_A5_del");
    A9->addNeighbourPort(A2, "STOP_A2_del");

    A3->addNeighbourPort(A1, "STOP_A1_del");
    A3->addNeighbourPort(A6, "STOP_A6_nyugat");
    A3->addNeighbourPort(A4, "STOP_A4_nyugat");

    A4->addNeighbourPort(A2, "STOP_A2_delnyugat");
    A4->addNeighbourPort(A3, "STOP_A3_kelet");
    A4->addNeighbourPort(A5, "STOP_A5_kelet");

    A5->addNeighbourPort(A9, "STOP_A9_eszaknyugat");
    A5->addNeighbourPort(A6, "STOP_A6_kelet");
    A5->addNeighbourPort(A4, "STOP_A4_kelet");

    A6->addNeighbourPort(A8, "STOP_A8_eszakkelet");
    A6->addNeighbourPort(A5, "STOP_A3_nyugat");
    A6->addNeighbourPort(A2, "STOP_A5_nyugat");
#endif
#ifdef DIAGONAL
    ECNJudge* A1 = (ECNJudge*)judgeMap["A1"];
    ECNJudge* A2 = (ECNJudge*)judgeMap["A2"];
    ECNJudge* A3 = (ECNJudge*)judgeMap["A3"];
    ECNJudge* A5 = (ECNJudge*)judgeMap["A5"];
    ECNJudge* A8 = (ECNJudge*)judgeMap["A8"];
    ECNJudge* A9 = (ECNJudge*)judgeMap["A9"];

    A1->addNeighbourPort(A2, "STOP_A2_nyugat");
    A1->addNeighbourPort(A3, "STOP_A3_eszaknyugat");
    A1->addNeighbourPort(A8, "STOP_A8_eszak");

    A2->addNeighbourPort(A9, "STOP_A2_eszak");
    A2->addNeighbourPort(A8, "STOP_A8_eszakkelet");
    A2->addNeighbourPort(A1, "STOP_A1_kelet");

    A8->addNeighbourPort(A1, "STOP_A1_del");
    A8->addNeighbourPort(A2, "STOP_A2_delnyugat");
    A8->addNeighbourPort(A9, "STOP_A9_nyugat");

    A9->addNeighbourPort(A8, "STOP_A8_kelet");
    A9->addNeighbourPort(A5, "STOP_A5_del");
    A9->addNeighbourPort(A2, "STOP_A2_del");

    A3->addNeighbourPort(A1, "STOP_A1_del");

    A5->addNeighbourPort(A9, "STOP_A9_eszaknyugat");

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
        if (j.second!=nullptr && j.second->initialized) j.second->step(now);
    }
}

void JudgeSystem::informJudges(void *message) {
    for (auto& jp: judgeMap){
        jp.second->informJudge(message);
    }
    delete message;
}