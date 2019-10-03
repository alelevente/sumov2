//
// Created by levente on 2018.07.31..
//

#ifndef SUMO_CONFLICTCLASS_H
#define SUMO_CONFLICTCLASS_H


#include <vector>
#include <libsumo/TraCIDefs.h>
#include "AbstractJudge.h"


#define MAX_CC_MEMBERS 10
#define IN_DANGER 10
//#define IN_DANGER inDanger-5

class MSDevice_SAL;
class Group;
enum JudgeCommand;

/**
 * @brief Base class for implementing further conflict classes
 */
class ConflictClass {
    //for better performance:
    friend class RRJudge;

    /// @brief If a smart car is inside this perimeter it is in danger
    int inDanger = 35;
protected:
    /// @brief list of smart cars which are in this conflict class
    std::vector<MSDevice_SAL*> myCars;
    /// @brief color for graphical representation
    libsumo::TraCIColor myColor;
public:
    /**
     * @brief Constructor
     * @param dangerRadius custom inDanger radius
     */
    ConflictClass(int dangerRadius);
    /// @brief Constructor
    ConflictClass();
    /// @brief This method is responsible for calculate the price, the 'priority' of this conflict class
    virtual double calculatePrice();
    /// @brief getter of the conflict class's color
    const libsumo::TraCIColor& getMyColor();

    /**
     * @brief The conflict class optionally decide if a smart car can join it
     * @param nMembers number of vehicles of the group which want to join this conflict class
     * @param inDirection entry marker's name
     * @param outDirection exit marker's name
     * @return true if the incoming group can join this conflict class
     */
    virtual bool canJoinGroup(int nMembers, const std::string& inDirection, const std::string& outDirection);

    /**
     * @brief called if a group is about to join the conflict class
     * @param group the group who wants to join
     */
    virtual void joinGroup(Group* group);

    /**
     * @brief called if a smart car's group had already joined to this conflict class before the smart car joined this group
     * @param sal pointer to the smart car's simulation abstraction device
     */
    virtual void addVehicle(MSDevice_SAL* sal);

    /**
     * @brief called if a smart car has left the intersection
     * @param sal pointer to the smart car's simulation abstraction device
     */
    virtual void removeVehicle(MSDevice_SAL* sal);

    /**
     * @brief the conflict class look for a specified smart car
     * @param vehicle pointer to the smart car's simulation abstraction device
     * @return true if the conflict class has the smart car in its list of smart cars
     */
    bool hasVehicle(MSDevice_SAL* vehicle);

    /// @brief Returns true if there are no smart cars in this conflict class
    bool isEmpty();
    /**
     *
     * @param x X coordinate of the intersection's center
     * @param y Y coordinate of the intersection's center
     * @return true, if there are cars inside the intersection (or cannot stop in time)
     */
    bool isThereCarInDanger(double x, double y);

    /// @brief Returns true if there are smart cars which can pass through the intersection in an actual green phase
    bool isFirst();

    /// @brief Inform all cars in the Conflict Class about the judge's decision
    virtual void informCars(JudgeCommand jc);
};


#endif //SUMO_CONFLICTCLASS_H
