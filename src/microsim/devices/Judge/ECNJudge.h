//
// Created by levente on 2019.09.16..
//

#ifndef SUMO_ECNJUDGE_H
#define SUMO_ECNJUDGE_H


#include <map>
#include "AbstractJudge.h"

class ECNJudge: public AbstractJudge {
public:
    ECNJudge(const std::string &path);
    void step(const SUMOTime &st) override;

    bool canPass(MSDevice_SAL *who, const std::string &direction) override;

    ~ECNJudge();

protected:
    int decideCC(Group *group, const std::string &direction) override;

    void changeCC() override;

private:
    int** conflictMtx;
    std::map<MSDevice_SAL*, std::string> directionByCars;
    std::map<std::string, SUMOTime> directionTimes;
    std::map<std::string, int> directions;
    bool* candidatesForNextActivePhase;
    int nDirections = 0;
    bool candidatesCalculated = false;
    void calculateCandidates();
    SUMOTime now, lastChanged = 0;
};




#endif //SUMO_ECNJUDGE_H
