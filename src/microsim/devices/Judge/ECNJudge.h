//
// Created by levente on 2019.09.16..
//

#ifndef SUMO_ECNJUDGE_H
#define SUMO_ECNJUDGE_H


#include <map>
#include "AbstractJudge.h"

class ECNJudge;

struct ECNNotification{
    ECNJudge* sender;
    std::string direction;
    bool congested;
};

class ECNJudge: public AbstractJudge {
public:
    ECNJudge(const std::string &path);
    void step(const SUMOTime &st) override;

    bool canPass(MSDevice_SAL *who, const std::string &direction) override;

    ~ECNJudge() override;
    void carLeftJunction(MSDevice_SAL* who, bool byForce = false) override;

    void informJudge(void* message);
    void addNeighbourPort(ECNJudge *neighbor, const std::string &port);

protected:
    int decideCC(Group *group, const std::string &direction) override;

    void changeCC() override;

private:
    int** conflictMtx;
    std::map<MSDevice_SAL*, std::string> directionByCars;
    std::map<std::string, SUMOTime> directionTimes;
    std::map<std::string, int> directions;

    std::map<ECNJudge*, std::string> portMap;
    std::map<ECNJudge*, bool> congestionMap;
    std::map<std::string, double> myPortLimitMap;
    std::map<std::string, double*> myPortStateMap;
    std::vector<std::string> portDirections;
    std::map<std::string, std::string> directionToPortMap;

    bool* candidatesForNextActivePhase;
    double* portStates;
    int nDirections = 0;
    bool candidatesCalculated = false;
    void calculateCandidates();
    SUMOTime now, lastChanged, yellowStarted, lastECN, lastStepLengthCalc = -25000;
    bool yellow = false;
    void makeGreen();
    void informOthers();
    long stepLength = 25000;
    void calculateStepLength();
};




#endif //SUMO_ECNJUDGE_H
