//
// Created by levente on 2018.08.01..
//

#include "libsumo/Simulation.h"
#include <fstream>
#include <iostream>
#include "RRJudge.h"



RRJudge::RRJudge(const std::string &path) {
    activeCC = 0;
    std::ifstream input(path,std::ifstream::in);

    input >> nDirs; input >> nPrograms;
    std::string in;
    for (int i=0; i<nDirs; ++i) {
        input >> in;
        std::string* myStr = new std::string(in);
        directions.insert(directions.end(), myStr);
    }
    int inNum;
    for (int i=0; i<nPrograms; ++i) {
        ProgramElement* pe = new ProgramElement();
        ConflictClass* cc = new ConflictClass();
        conflictClasses.insert(conflictClasses.end(), cc);
        for (int j=0; j<nDirs; ++j) {
            input >> inNum;
            pe->passeable.insert(pe->passeable.end(), (inNum == 1));
        }
        input >> pe->duration;
        programElements.insert(programElements.end(), pe);
    }
    input.close();
}

RRJudge::~RRJudge() {
    for (int i=0; i<nDirs; ++i)
        delete directions[i];
    for (int i=0; i<nPrograms; ++i)
        delete programElements[i];
}

void RRJudge::changeCC() {
    //std::cout << *directions[0] << " came in: " << cameIn << "\twent out: "<< wentOut << " " << conflictClasses[activeCC] -> isEmpty() <<std::endl;

    if (cameIn == wentOut) {
        int currentTime = (int) libsumo::Simulation::getCurrentTime()/1000;
        if (yellow && flaggedAt+3<=currentTime) {
            startTime = currentTime;
            activeCC = nextActiveCC;
            yellow = false;
            lastCameIn = currentTime;
        }
        int kor = activeCC;
        if (currentTime-startTime > programElements[activeCC]->duration
                || conflictClasses[activeCC]->isEmpty() || currentTime - lastCameIn > 3) {
            do {
                nextActiveCC = (activeCC == nPrograms - 1) ? 0 : activeCC + 1;
            } while (conflictClasses[activeCC]->isEmpty() && activeCC != kor);
            if (conflictClasses[activeCC]->isThereCarInDanger(posX, posY)) {
                yellow = true;
                lastCameIn = currentTime;
                flaggedAt = currentTime;
            } else {
                startTime = currentTime;
                activeCC = nextActiveCC;
                yellow = false;
                lastCameIn = currentTime;
            }

            //std::cout << *directions[0] << std::endl;
        }
    }
}

int RRJudge::decideCC(Group *group, const std::string &direction) {
    int dir = 0;
    for (dir = 0; *directions[dir]!=direction && dir<nDirs; ++dir);
    int acc;
    for (acc=0; !programElements[acc]->passeable[dir] && acc<nPrograms; ++acc);
    conflictClasses[acc]->joinGroup(group);
    return acc;
}

bool RRJudge::canPass(MSDevice_SAL *who) {
    int now = (int) libsumo::Simulation::getCurrentTime() / 1000;
    if (now - startTime > programElements[activeCC]->duration
            || now-lastCameIn > 3) changeCC();
    return !yellow && conflictClasses[activeCC]->hasVehicle(who);
}