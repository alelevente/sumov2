//
// Created by levente on 2018.06.20..
//

#ifndef SUMO_MSDEVICE_SAL_H
#define SUMO_MSDEVICE_SAL_H

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

#include "MSDevice.h"
#include <utils/common/SUMOTime.h>
#include <libsumo/TraCIDefs.h>
#include <microsim/devices/Others/LCManager.h>
#include <microsim/devices/Judge/AbstractJudge.h>
#include <microsim/lcmodels/MSLCM_SmartSL2015.h>
#include "GroupingSystem/Group.h"


#define GROUP_GAP_DESIRED 5
#define GROUP_GAP_THRESHOLD 3
#define GROUP_GAP_LIMIT 2


// ===========================================================================
// class declarations
// ===========================================================================
class SUMOVehicle;
class MSLCM_SmartSL2015;
class LCManager;
class Messenger;
class AbstractJudge;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class MSDevice_SAL
 * @brief A device which collects info on the vehicle trip (mainly on departure and arrival)
 *
 * Each device collects departure time, lane and speed and the same for arrival.
 *
 * @see MSDevice
 */
class MSDevice_SAL : public MSDevice {
public:
    /** @brief Inserts MSDevice_SAL-options
     * @param[filled] oc The options container to add the options to
     */
    static void insertOptions(OptionsCont& oc);


    /** @brief Build devices for the given vehicle, if needed
     *
     * The options are read and evaluated whether a SAL-device shall be built
     *  for the given vehicle.
     *
     * The built device is stored in the given vector.
     *
     * @param[in] v The vehicle for which a device may be built
     * @param[filled] into The vector to store the built device in
     */
    static void buildVehicleDevices(SUMOVehicle& v, std::vector<MSDevice*>& into);



public:
    /// @brief Destructor.
    ~MSDevice_SAL();



    /// @name Methods called on vehicle movement / state change, overwriting MSDevice
    /// @{

    /** @brief Checks for waiting steps when the vehicle moves
     *
     * @param[in] veh Vehicle that asks this reminder.
     * @param[in] oldPos Position before move.
     * @param[in] newPos Position after move with newSpeed.
     * @param[in] newSpeed Moving speed.
     *
     * @return True (always).
     */
    bool notifyMove(SUMOVehicle& veh, double oldPos,
                    double newPos, double newSpeed);


    /** @brief Saves departure info on insertion
     *
     * @param[in] veh The entering vehicle.
     * @param[in] reason how the vehicle enters the lane
     * @return Always true
     * @see MSMoveReminder::notifyEnter
     * @see MSMoveReminder::Notification
     */
    bool notifyEnter(SUMOVehicle& veh, MSMoveReminder::Notification reason, const MSLane* enteredLane = 0);


    /** @brief Saves arrival info
     *
     * @param[in] veh The leaving vehicle.
     * @param[in] lastPos Position on the lane when leaving.
     * @param[in] isArrival whether the vehicle arrived at its destination
     * @param[in] isLaneChange whether the vehicle changed from the lane
     * @return True if it did not leave the net.
     */
    bool notifyLeave(SUMOVehicle& veh, double lastPos,
                     MSMoveReminder::Notification reason, const MSLane* enteredLane = 0);
    /// @}


    /// @brief return the name for this type of device
    const std::string deviceName() const {
        return "SAL";
    }

    /// @brief try to retrieve the given parameter from this device. Throw exception for unsupported key
    std::string getParameter(const std::string& key) const;

    /// @brief try to set the given parameter for this device. Throw exception for unsupported key
    void setParameter(const std::string& key, const std::string& value);

    /** @brief Called on writing tripinfo output
     *
     * @param[in] os The stream to write the information into
     * @exception IOError not yet implemented
     * @see MSDevice::generateOutput
     */
    void generateOutput() const;

private:
    /** @brief Constructor
     *
     * @param[in] holder The vehicle that holds this device
     * @param[in] id The ID of the device
     */
    MSDevice_SAL(SUMOVehicle& holder, const std::string& id, double customValue1,
                 double customValue2, double customValue3);
    // private state members of the SAL device

    /// @brief a value which is initialised based on a commandline/configuration option
    double myCustomValue1;

    /// @brief a value which is initialised based on a vehicle parameter
    double myCustomValue2;

    /// @brief a value which is initialised based on a vType parameter
    double myCustomValue3;

    libsumo::TraCIColor originalColor;
    int entryMarkerFlag = -1;

    /// @brief Invalidated copy constructor.
    MSDevice_SAL(const MSDevice_SAL&);

    /// @brief Invalidated assignment operator.
    MSDevice_SAL& operator=(const MSDevice_SAL&);

    bool hasReachedPONR(bool onStop);

/***********************************NON-SUMO originated codes********************************/
public:
    /// @brief for graphical representation of group and CC states
    void setVehicleColor (const libsumo::TraCIColor& color);
    /// @brief resets the graphical representation to its default
    void resetVehicleColor();
    /// @brief used to set a speed of a smart car
    void setVehicleSpeed (double speed);
    /// @brief sets group state to group leader
    void informBecomeLeader();
    /// @brief sets group state to group member
    void informBecomeMember(Group* group);
    /// @brief resets group state, as well switches back to "unintelligent" state
    AbstractJudge * informNoLongerLeader();

    /**
     * @brief called by MSLCM_SmartSl2015 if a lane change is finished
     * @param follower the follower group's leader
     * @param offset direction of lanechange
     * @return true if it is the last car of its group
     */
    bool laneChanged(MSLCM_SmartSL2015 *follower, int offset);

    /**
     * @brief called by MSLCM_SmartSl2015 if a lane change is needed
     * @param follower the follower group's leader
     * @param offset direction of lanechange
     */
    void laneChangeNeeded(MSLCM_SmartSL2015 *follower, int offset);
    /// @brief manages the group's lane change. @see LCManager
    void groupChanging(MSLCM_SmartSL2015 *follower);
    /// @brief A query about the smart car's group leader
    SUMOVehicle* getMyGroupLeader();
    /// @brief Pointer to the smart car itself
    SUMOVehicle* getVehicle();
    /// @brief Returns the length which the group occupies on the road
    double getGroupLength();

    /**
     * @brief MSLCM_SmartSl2015 calls this function when information exchange is needed between smart cars. If both smart cars are group leaders, and this car is blocker, then it has to stop.
     * @param blocker Who is the blocker (who has to stop)
     * @param leader Who is the leader (who may proceed)
     */
    void amBlocker(MSLCM_SmartSL2015* blocker, MSLCM_SmartSL2015* leader);
    /// @brief in a junction, it is the direction description, in form "entry marker's name-exit marker's name"
    std::string myDirection;
    /// @brief returns true, if there are no cars in front (in 20 m distance)
    bool isFirst();
    /// @brief SUMO bugfix
    bool locked = false;

    void informDecision(JudgeCommand jc);

    Group* getGroup();

    /// @brief pointer to the LCManager of this smart car
    LCManager* myLCm = nullptr;



private:
    double lastSetSpeed = 0;
    bool lastEdgeWasStop = false;

    /// @brief true, if this smart car is a member
    bool isMember = false;
    /// @brief true, it the judge has given permission to pass
    bool passPermitted = false;
    /// @brief true, if the smart car has already reported its coming to the judge
    bool reported = false;
    /// @brief true, if the smart car has passed the PONR (point of no return)
    bool inJunction = false;
    /// @brief true, if we have already reset the speed of the smart car
    bool speedSetInJunction = false;
    /// @brief if near a junction, it points to judge of this junction
    AbstractJudge* myJudge = nullptr;
public:
    AbstractJudge *getMyJudge() const;

private:
    /// @brief First-in-First-out list of the group leaders who made this car's lane changes possible
    std::vector<MSLCM_SmartSL2015*> followerFIFO;
    /// @brief pointer to this smart car's group
    Group* myGroup = nullptr;
    /// @brief the smart car in front of this car in a group
    Messenger* myLeaderMessenger = nullptr;
public:
    void setMyLeaderMessenger(Messenger *myLeaderMessenger);

private:
    /// @brief pointer to this smart car's lane change model
    MSLCM_SmartSL2015 *myLaneChangeModel = nullptr;
    int stopStartedLC = 0, passChanged = 0;
};

#endif //SUMO_MSDEVICE_SAL_H
