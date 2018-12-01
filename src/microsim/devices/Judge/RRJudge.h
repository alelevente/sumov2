//
// Created by levente on 2018.08.01..
//

#ifndef SUMO_RRJUDGE_H
#define SUMO_RRJUDGE_H

#include "microsim/devices/Judge/AbstractJudge.h"
#include "ConflictClass.h"
#include <vector>
#include <string>

class Group;
class MSDevice_SAL;

/// @brief List of program elements defined in a file. A program means a set of directions which can pass simultanously, they can form a CC.
struct ProgramElement {
    /// @brief can a direction pass in this program?
    std::vector<bool> passeable;
    /// @brief maximum amount of time which can have this program (roughly a CC)
    int duration;
};

/// @brief This CC implements RR judge
class RRJudge: public AbstractJudge {
    /**
     * @brief This function decides which conflict class is suitable for an incoming group
     * @param group incoming group
     * @param direction Direction description of the group in form "entry marker's name-exit marker's name"
     * @return index of the decided conflict class
     */
    virtual int decideCC(Group *group, const std::string &direction);
    /// @brief list of program elements
    std::vector<ProgramElement*> programElements;
    /// @brief list of direction description
    std::vector<std::string*> directions;
    /// @brief time stamp since last change of CCs
    int startTime = 0;
    /// @brief number of directions
    int nDirs = 0;
    /// @brief number of programs
    int nPrograms = 0;

    /// @brief calculation of change is not necesarry, if there are smart cars only in one CC or there are no cars present
    bool changeNeeded();

    /// @brief This override function is responsible for selecting the new CC in case of need
    virtual void changeCC();

protected:
    /// @brief yellow is the transition state of changing CCs
    bool yellow = false;
    /// @brief the next CC can be decided before the actual change. This value stores its index.
    int nextActiveCC = 0;
    /// @brief the next CC can be decided before the actual change. This value stores the decision's time stamp
    int flaggedAt = 0;

public:
    /// @brief constructor
    RRJudge(const std::string& path);
    /// @brief destructor
    ~RRJudge();
    /// @brief override of canPass @see AbstractJudge
    bool canPass(MSDevice_SAL* who);
};


#endif //SUMO_RRJUDGE_H
