//
// Created by levente on 2018.08.08..
//

#ifndef SUMO_JUDGESYSTEM_H
#define SUMO_JUDGESYSTEM_H

#include <string>
#include <map>
#include "microsim/devices/Judge/AbstractJudge.h"

class AbstractJudge;

/// @brief Singleton class for managing the judges
class JudgeSystem {
    /// @brief list of judges
    std::map<std::string, AbstractJudge*> judgeMap;
    /// @brief constructor
    JudgeSystem();
    /// @brief destructor
    ~JudgeSystem();
    /// @brief deactivated copy ctor
    JudgeSystem(JudgeSystem const&);
    /// @brief deactivated eq. operator
    void operator=(const JudgeSystem&);

public:
    /// @brief return this singleton instance
    static JudgeSystem& getInstance();
    /**
     * @brief kind of a getter of judges
     * @param name the name of the judge in question
     * @return pointer the the judge instance
     */
    AbstractJudge* getJudgeByName(const std::string& name);
};


#endif //SUMO_JUDGESYSTEM_H
