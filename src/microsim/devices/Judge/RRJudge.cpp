//
// Created by levente on 2018.08.01..
//


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
        ConflictClass* cc = new ConflictClass(stopRadius);
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

    if (cameIn == wentOut) {
        bool carInDanger = conflictClasses[activeCC]->isThereCarInDanger(posX, posY);
        int currentTime = (int) libsumo::Simulation::getCurrentTime()/1000;
        if (yellow && flaggedAt+3<=currentTime && !carInDanger) {
            startTime = currentTime;
            activeCC = nextActiveCC;
            yellow = false;
            lastCameIn = currentTime;
            return;
        }
        int kor = activeCC;
        if (currentTime-startTime > programElements[activeCC]->duration
                || conflictClasses[activeCC]->isEmpty() || currentTime - lastCameIn > 3) {
            nextActiveCC = activeCC;
            if (changeNeeded() || conflictClasses[activeCC]->isEmpty())
            do {
                nextActiveCC = (nextActiveCC == nPrograms - 1) ? 0 : nextActiveCC + 1;
            } while (conflictClasses[nextActiveCC]->isEmpty() && nextActiveCC != kor
                     && !conflictClasses[nextActiveCC]->isFirst());
            if (carInDanger) {
                yellow = true;
                lastCameIn = currentTime;
                flaggedAt = currentTime;
            } else {
                startTime = currentTime;
                activeCC = nextActiveCC;
                yellow = false;
                lastCameIn = currentTime;
            }
        }
    } else {
        ;
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

bool RRJudge::canPass(MSDevice_SAL *who, const std::string &direction) {
    int now = (int) libsumo::Simulation::getCurrentTime() / 1000;
    if (now - lastCheck > 1) {
        this->makeKill();
        lastCheck = now;
    }
    if (now - startTime > programElements[activeCC]->duration
            || now-lastCameIn > 3) changeCC();
    return !yellow && (now - startTime <= programElements[activeCC]->duration) && allowedToMove(who, &who->myDirection);
}

bool RRJudge::changeNeeded() {
    int count = 0;
    for (auto i= conflictClasses.begin(); i != conflictClasses.end(); ++i){
        if (!(*i)->isEmpty()) ++count;
        if (count == 2) return true;
    }
    return false;
}

bool RRJudge::allowedToMove(MSDevice_SAL *who, std::string *direction) {
    if (conflictClasses[activeCC]->hasVehicle(who) || direction == nullptr) return true;
    int dir = 0;
    for (dir = 0; dir<nDirs && *directions[dir]!=*direction; ++dir);
    return programElements[activeCC]->passeable[dir]? true: false;
}