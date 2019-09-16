//
// Created by levente on 2018.08.01..
//
#include <fstream>
#include <iostream>
#include "MDDFConflictClass.h"
#include "MDDFJudge.h"
#include "libsumo/Simulation.h"


MDDFJudge::MDDFJudge(const std::string &path) {
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
        ConflictClass* cc = new MDDFConflictClass(stopRadius);
        conflictClasses.insert(conflictClasses.end(), cc);
        for (int j=0; j<nDirs; ++j) {
            input >> inNum;
            pe->passeable.insert(pe->passeable.end(), (inNum == 1));
        }
        input >> pe->duration;
        programElements.insert(programElements.end(), pe);
    }
    input.close();
    this->initialized = true;
}

MDDFJudge::~MDDFJudge() {
    for (int i=0; i<nDirs; ++i)
        delete directions[i];
    for (int i=0; i<nPrograms; ++i)
        delete programElements[i];
}

void MDDFJudge::step(const SUMOTime &now) {
    currentTime = now / 1000;
    if (now - lastCheck > 1) {
        this->makeKill();
        lastCheck = now;
    }
    if (now - startTime > programElements[activeCC]->duration
        || now-lastCameIn > 3) changeCC();
}

void MDDFJudge::changeCC() {
    if (cameIn == wentOut) {
        bool carInDanger = conflictClasses[activeCC]->isThereCarInDanger(posX, posY);
        //int currentTime = (int) libsumo::Simulation::getCurrentTime()/1000;
        if (yellow && flaggedAt+3<=currentTime && !carInDanger) {
            startTime = currentTime;
            ((MDDFConflictClass*)conflictClasses[activeCC])->setLastTime(currentTime);

            conflictClasses[activeCC]->informCars(JC_STOP);
            activeCC = nextActiveCC;
            conflictClasses[activeCC]->informCars(JC_GO);

            ((MDDFConflictClass*)conflictClasses[activeCC])->resetBadGuy();
            yellow = false;
            lastCameIn = currentTime;
        }
        int kor = activeCC;
        if (!yellow && currentTime-startTime > programElements[activeCC]->duration
            || conflictClasses[activeCC]->isEmpty() || currentTime - lastCameIn > 3) {
            if (currentTime - lastCameIn > 3) ((MDDFConflictClass*)conflictClasses[activeCC])->setBadGuy();
            if ((changeNeeded() || conflictClasses[activeCC]->isEmpty()) && nextActiveCC==activeCC) {
                nextActiveCC = selectNextCC();
            }
            if (carInDanger) {
                conflictClasses[activeCC]->informCars(JC_STOP);
                yellow = true;
                lastCameIn = currentTime;
                flaggedAt = currentTime;
            } else {
                startTime = currentTime;
                conflictClasses[activeCC]->informCars(JC_STOP);
                activeCC = nextActiveCC;
                conflictClasses[activeCC]->informCars(JC_GO);
                yellow = false;
                lastCameIn = currentTime;
            }
        }
    } else {
        conflictClasses[activeCC]->informCars(JC_STOP);
    }
}

int MDDFJudge::decideCC(Group *group, const std::string &direction) {
    std::cout << direction << std::endl;
    int dir = 0;
    for (dir = 0; *directions[dir]!=direction && dir<nDirs; ++dir);
    //SUMO's bugfix:
    if (dir>=nDirs) return 0;
    int acc;
    for (acc=0; !programElements[acc]->passeable[dir] && acc<nPrograms; ++acc);
    conflictClasses[acc]->joinGroup(group);
    if (acc==activeCC) {
        JudgeCommand canGo = yellow ? JC_STOP : JC_GO;
        conflictClasses[acc]->informCars(canGo);
    } else conflictClasses[acc]->informCars(JC_STOP);
    return acc;
}

bool MDDFJudge::canPass(MSDevice_SAL *who, const std::string &direction) {
    long long int now = currentTime;

    return !yellow && (now - startTime <= programElements[activeCC]->duration) && conflictClasses[activeCC]->hasVehicle(who);
}

int MDDFJudge::selectNextCC() {
    int minCC = 0, j = 0;
    double min = 10000;
    j = lastRR;
    std::cout << *directions[0];

    //First priority: RR
    do {
        j = (j >= conflictClasses.size() - 1) ? 0 : j + 1;
        if (!(conflictClasses[j])->isEmpty() &&
                ((MDDFConflictClass*)(conflictClasses[j]))->isOld() &&
                ((MDDFConflictClass*)(conflictClasses[j]))->isFirst()) {
            lastRR = j;
            return j;
        }
    } while (j!=lastRR);

    //Second priority: MDDF
    j=0;
    std::cout << "(";
    for (auto i = conflictClasses.begin(); i != conflictClasses.end(); ++i) {
        if (((MDDFConflictClass*)(*i))->isFirst()) {
            double k = (*i)->calculatePrice();
            std::cout << k << ", ";
            if (k < min && k >= 0) {
                min = k;
                minCC = j;
            }
        }
        ++j;
    }
    std::cout << ") " << minCC << std::endl;
    return minCC;
}

bool MDDFJudge::changeNeeded() {
    int count = 0;
    for (auto i= conflictClasses.begin(); i != conflictClasses.end(); ++i){
        if (!(*i)->isEmpty()) ++count;
        if (count == 2) return true;
    }
    return false;
}