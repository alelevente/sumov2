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
#include "GroupingSystem/Group.h"


#define GROUP_GAP_DESIRED 12
#define GROUP_GAP_THRESHOLD 3
#define GROUP_GAP_LIMIT 7


// ===========================================================================
// class declarations
// ===========================================================================
class SUMOVehicle;
class MSLCM_SmartSL2015;
class LCManager;
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

/***********************************NON-SUMO originated functions********************************/
public:
    void setVehicleColor (const libsumo::TraCIColor& color);
    void resetVehicleColor();
    void setVehicleSpeed (double speed);
    void informBecomeLeader();
    void informBecomeMember(Group* group);
    void informNoLongerLeader();
    bool laneChanged(MSLCM_SmartSL2015 *follower, int offset);
    void laneChangeNeeded(MSLCM_SmartSL2015 *follower, int offset);
    void groupChanging(MSLCM_SmartSL2015 *follower);
    void groupChangeFinished();
    bool isGroupChanging();
    MSLCM_SmartSL2015* getGroupFollowerLC();
    SUMOVehicle* getMyGroupLeader();
    SUMOVehicle* getVehicle();
    double getGroupLength();
    int getMemberCount();
    void informStoppedToContinue(MSLCM_SmartSL2015* stopped);
    void addFollower(MSLCM_SmartSL2015* follower);
    void amBlocker(MSLCM_SmartSL2015* blocker, MSLCM_SmartSL2015* leader);
    std::string myDirection;
    bool isFirst();

private:
    bool isMember = false, passPermitted = false,
         reported = false, inJunction = false,
         speedSetInJunction = false;
    LCManager* myLCm = nullptr;
    AbstractJudge* myJudge = nullptr;
    std::vector<MSLCM_SmartSL2015*> followerFIFO;

private:
    /** @brief Constructor
     *
     * @param[in] holder The vehicle that holds this device
     * @param[in] id The ID of the device
     */
    MSDevice_SAL(SUMOVehicle& holder, const std::string& id, double customValue1,
                     double customValue2, double customValue3);



private:
    // private state members of the SAL device

    /// @brief a value which is initialised based on a commandline/configuration option
    double myCustomValue1;

    /// @brief a value which is initialised based on a vehicle parameter
    double myCustomValue2;

    /// @brief a value which is initialised based on a vType parameter
    double myCustomValue3;

    libsumo::TraCIColor originalColor;
    int entryMarkerFlag = -1;

private:
    /// @brief Invalidated copy constructor.
    MSDevice_SAL(const MSDevice_SAL&);

    /// @brief Invalidated assignment operator.
    MSDevice_SAL& operator=(const MSDevice_SAL&);


};

#endif //SUMO_MSDEVICE_SAL_H