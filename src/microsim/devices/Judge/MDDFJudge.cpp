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
        ConflictClass* cc = new MDDFConflictClass();
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

MDDFJudge::~MDDFJudge() {
    for (int i=0; i<nDirs; ++i)
        delete directions[i];
    for (int i=0; i<nPrograms; ++i)
        delete programElements[i];
}

void MDDFJudge::changeCC() {
    //std::cout << *directions[0] << " came in: " << cameIn << "\twent out: "<< wentOut << " " << conflictClasses[activeCC] -> isEmpty() <<std::endl;

    if (cameIn == wentOut) {
        int currentTime = (int) libsumo::Simulation::getCurrentTime()/1000;
        if (yellow && flaggedAt+3<=currentTime) {
            startTime = currentTime;
            ((MDDFConflictClass*)conflictClasses[activeCC])->setLastTime(currentTime);
            activeCC = nextActiveCC;
            ((MDDFConflictClass*)conflictClasses[activeCC])->resetBadGuy();
            yellow = false;
            lastCameIn = currentTime;
        }
        int kor = activeCC;
        if (currentTime-startTime > programElements[activeCC]->duration
            || conflictClasses[activeCC]->isEmpty() || currentTime - lastCameIn > 3) {
            if (currentTime - lastCameIn > 3) ((MDDFConflictClass*)conflictClasses[activeCC])->setBadGuy();
            do {
                nextActiveCC = selectNextCC();
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

int MDDFJudge::decideCC(Group *group, const std::string &direction) {
    int dir = 0;
    for (dir = 0; *directions[dir]!=direction && dir<nDirs; ++dir);
    int acc;
    for (acc=0; !programElements[acc]->passeable[dir] && acc<nPrograms; ++acc);
    conflictClasses[acc]->joinGroup(group);
    return acc;
}

bool MDDFJudge::canPass(MSDevice_SAL *who) {
    int now = (int) libsumo::Simulation::getCurrentTime() / 1000;
    if (now - startTime > programElements[activeCC]->duration
        || now-lastCameIn > 3) changeCC();
    return !yellow && conflictClasses[activeCC]->hasVehicle(who);
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