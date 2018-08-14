//
// Created by levente on 2018.08.01..
//

#include "libsumo/Simulation.h"
#include <fstream>
#include "RRJudge.h"



RRJudge::RRJudge(const std::string &path) {
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
            input >> pe->duration;
        }
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
    if (cameIn == wentOut) {
        activeCC = (activeCC==nPrograms-1)? 0: activeCC+1;
        startTime =(int) libsumo::Simulation::getCurrentTime()/1000;
    }
}

int RRJudge::decideCC(Group *group, const std::string &direction) {
    int dir = 0;
    for (dir = 0; *directions[dir]!=direction && dir<nDirs; ++dir);
    int acc;
    for (acc=0; !programElements[acc]->passeable[dir] && acc<nPrograms; ++acc);
    conflictClasses[dir]->joinGroup(group);
    return acc;
}

bool RRJudge::canPass(MSDevice_SAL *who) {
    int now = (int) libsumo::Simulation::getCurrentTime() / 1000;
    if (startTime-now > programElements[activeCC]->duration) changeCC();
    return conflictClasses[activeCC]->hasVehicle(who);
}