//
// Created by levente on 2018.08.26..
//

#include <microsim/devices/MessagingSystem/MessengerSystem.h>
#include <microsim/devices/MessagingSystem/MessagingProxy.h>
#include "MDDFJudge.h"
#include "MDDFConflictClass.h"
#include "libsumo/Simulation.h"
#include "libsumo/Vehicle.h"

MDDFJudge::MDDFJudge(const std::string& path){
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

bool MDDFJudge::canPass(MSDevice_SAL *who) {
    int now = (int) libsumo::Simulation::getCurrentTime() / 1000;
    if (now - startTime > 7) changeCC();
    return conflictClasses[activeCC]->hasVehicle(who);
}

int MDDFJudge::decideCC(Group *group, const std::string &direction) {
    int dir = 0;
    for (dir = 0; *directions[dir]!=direction && dir<nDirs; ++dir);
    int acc;
    for (acc=0; !programElements[acc]->passeable[dir] && acc<nPrograms; ++acc);
    conflictClasses[acc]->joinGroup(group);
    return acc;
}

void MDDFJudge::changeCC() {
    std::cout << *(this->directions[0]) << " came in: " << cameIn << "\twent out: "<< wentOut << std::endl;
    if (cameIn == wentOut) {
        int minCC = 0, j = 0;
        double min = 10000;
        for (auto i = conflictClasses.begin(); i != conflictClasses.end(); ++i) {
            double k = (*i)->calculatePrice();
            if (k < min && k>=0) {
                min = k;
                minCC = j;
            }
            ++j;
        }

        activeCC = minCC;
        startTime =(int) libsumo::Simulation::getCurrentTime()/1000;
    } else {
#ifdef KILLCARS
        if (libsumo::Simulation::getCurrentTime() - lastCIChanged > 10000) {
            for (auto i = carsIn.begin(); i != carsIn.end(); ++i) {
                if (conflictClasses[activeCC]->hasVehicle(MessagingProxy::getInstance().getMessenger(*(*i))->mySAL)) {
                    conflictClasses.at(activeCC)->removeVehicle(MessagingProxy::getInstance().getMessenger(*(*i))->mySAL);
                } else {
                    for (int j = 0; j < conflictClasses.size(); ++j) {
                        if (conflictClasses[j]->hasVehicle(MessagingProxy::getInstance().getMessenger(*(*i))->mySAL)) {
                            conflictClasses.at(j)->removeVehicle(
                                    MessagingProxy::getInstance().getMessenger(*(*i))->mySAL);
                        }
                    }
                }
                libsumo::Vehicle::remove(*(*i));
            }
            cameIn = 0;
            wentOut = 0;
            lastCIChanged = libsumo::Simulation::getCurrentTime();
            carsIn.erase(carsIn.begin(), carsIn.end());
        }
#endif
        if (libsumo::Simulation::getCurrentTime() - lastCIChanged > 10000) {
            ((MDDFConflictClass *) conflictClasses[activeCC])->makeOlder();
            cameIn = 0;
            wentOut = 0;
        }
    }
}