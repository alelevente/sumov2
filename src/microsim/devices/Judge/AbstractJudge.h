//
// Created by levente on 2018.07.31..
//

#ifndef SUMO_ABSTRACTJUDGE_H
#define SUMO_ABSTRACTJUDGE_H

#include <string>
#include <vector>

#define REPORT_DISTANCE 100
#define STOP_DISTANCE 20


class MSDevice_SAL;
class Group;
class ConflictClass;

/**
 * @brief Abstract base class for implementing concrete judges
 */
class AbstractJudge {
protected:
    /// @brief list of conflict classes which are present in the junction
    std::vector<ConflictClass*> conflictClasses;

    /**
     * @brief Abstract method to decide which conflict class a newly coming group can join to.
     * @param group The incoming group.
     * @param direction Direction description of the group in form "entry marker's name-exit marker's name"
     * @return The index of the appropriate conflict class.
     */
    virtual int decideCC(Group *group, const std::string &direction) = 0;

    /// @brief This method is responsible for changing the active conflict class
    virtual void changeCC() =0;
    /// @brief Active CC is the conflict class who can currently pass through the intersection
    int activeCC = -1;
    /// @brief number of smart cars entered the intersection
    int cameIn = 0;
    /// @brief number of smart cars exited the intersection
    int wentOut = 0;
    /// @brief timestamp of the last smart car's entering the intersection
    long int lastCameIn = 0;
    /// @brief timestamp of the last check for stucked vehicles
    int lastCheck = 0;
    /// @brief list of cars that are currently inside of the intersection
    std::vector<MSDevice_SAL*> carsIn;
    /// @brief This function is called periodically to kill stucked smart vehicles
    void makeKill();

#ifdef KILLCARS
    std::vector <std::string*> carsIn;
#endif
    long int lastCIChanged;


public:
    /// @brief x coordinate of the center of the intersection
    double posX;
    /// @brief y coordinate of the center of the intersection
    double posY;
    /// @brief the radius of stopping distance around the intersection
    double stopRadius = 15;
    /// @brief the radius of Point of No Return around the intersection
    double ponrRadius = 5;

    /**
     * @brief May be called if the last smart car of a conflict class has left the junction
     * @param cc the Conflict Class of which the last car has left
     */
    virtual void informCCEnded(ConflictClass* cc);

    /**
     * @brief Judge's answer if a smart car asks whether it can pass or not.
     * @param who the car who is curious if it can currently pass through the intersection
     * @return true if the car is allowed to go through the intersection
     */
    virtual bool canPass(MSDevice_SAL *who, const std::string &direction)=0;

    /**
     * @brief Smart cars inform AbstractJudge about entering the intersection
     * @param who the smart car who reports its coming
     */
    virtual void carPassedPONR(MSDevice_SAL* who);

    /**
     * @brief Smart cars inform AbstractJudge about leaving the intersection
     * @param who the smart car who reports its leaving
     * @param byForce true, if the smart car has been killed by method makeKill()
     */
    virtual void carLeftJunction(MSDevice_SAL* who, bool byForce = false);

    /**
     * @brief Smart cars inform AbstractJudge about nearing the intersection
     * @param group the group who is going to come into the intersection
     * @param direction Direction description of the group in form "entry marker's name-exit marker's name"
     */
    virtual void reportComing(Group *group, const std::string &direction);

    /// @brief destructor
    virtual ~AbstractJudge();
};


#endif //SUMO_ABSTRACTJUDGE_H
