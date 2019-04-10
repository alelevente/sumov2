//
// Created by levente on 2018.08.26..
//

#ifndef SUMO_MDDFJUDGE_H
#define SUMO_MDDFJUDGE_H


#include <microsim/devices/GroupingSystem/Group.h>
#include "RRJudge.h"

/// @brief This class implements the MDDF judge.
class MDDFJudge: public AbstractJudge {
    /**
     * @brief This function decides which conflict class is suitable for an incoming group
     * @param group incoming group
     * @param direction Direction description of the group in form "entry marker's name-exit marker's name"
     * @return index of the decided conflict class
     */
    virtual int decideCC(Group *group, const std::string &direction);
    /// @brief list of direction description
    std::vector<std::string*> directions;
    /// @brief time stamp since last change of CCs
    int startTime = 0;
    /// @brief number of directions
    int nDirs = 0;
    /// @brief number of programs
    int nPrograms = 0;
    /**
     * @brief List of program elements defined in a file. A program means a set of directions which can pass simultanously, they can form a CC.
     */
    std::vector<ProgramElement*> programElements;

    /// @brief This override function is responsible for selecting the new CC in case of need
    virtual void changeCC();
    /// @brief This function is a helper for changeCC
    int selectNextCC();

    /// @brief yellow is the transition state of changing CCs
    bool yellow = false;
    /// @brief the next CC can be decided before the actual change. This value stores its index.
    int nextActiveCC = 0;
    /// @brief the next CC can be decided before the actual change. This value stores the decision's time stamp
    int flaggedAt = 0;
    /// @brief this value stores the index of the Round Robin row
    int lastRR=0;

    /// @brief calculation of change is not necesarry, if there are smart cars only in one CC or there are no cars present
    bool changeNeeded();

public:
    /// @brief constructor
    MDDFJudge(const std::string& path);
    /// @brief destructor
    ~MDDFJudge();
    /// @brief override of canPass @see AbstractJudge
    bool canPass(MSDevice_SAL *who, const std::string &direction);
};


#endif //SUMO_MDDFJUDGE_H
