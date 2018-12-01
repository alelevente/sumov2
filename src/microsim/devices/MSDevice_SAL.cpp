//
// Created by levente on 2018.06.20..
//

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>
#include <string>
#include <utils/common/TplConvert.h>
#include <utils/options/OptionsCont.h>
#include <utils/iodevices/OutputDevice.h>
#include <utils/vehicle/SUMOVehicle.h>
#include <microsim/MSNet.h>
#include <microsim/MSLane.h>
#include <microsim/MSEdge.h>
#include <microsim/MSVehicle.h>
#include <microsim/devices/MessagingSystem/MessengerSystem.h>
#include <microsim/devices/MessagingSystem/MessagingProxy.h>
#include <libsumo/VehicleType.h>
#include <libsumo/Vehicle.h>
#include "MSDevice_Tripinfo.h"
#include "MSDevice_SAL.h"

#include "microsim/devices/MarkerSystem/MarkerSystem.h"

// ===========================================================================
// method definitions
// ===========================================================================
// ---------------------------------------------------------------------------
// static initialisation methods
// ---------------------------------------------------------------------------
void
MSDevice_SAL::insertOptions(OptionsCont& oc) {
    oc.addOptionSubTopic("SAL Device");
    insertDefaultAssignmentOptions("SAL", "SAL Device", oc);

    oc.doRegister("device.SAL.parameter", new Option_Float(0.0));
    oc.addDescription("device.SAL.parameter", "SAL Device", "An exemplary parameter which can be used by all instances of the SAL device");
}


void
MSDevice_SAL::buildVehicleDevices(SUMOVehicle& v, std::vector<MSDevice*>& into) {
    OptionsCont& oc = OptionsCont::getOptions();
    if (equippedByDefaultAssignmentOptions(oc, "SAL", v, false)) {
        // build the device
        // get custom vehicle parameter
        double customParameter2 = -1;
        if (v.getParameter().knowsParameter("SAL")) {
            try {
                customParameter2 = TplConvert::_2double(v.getParameter().getParameter("SAL", "-1").c_str());
            } catch (...) {
                WRITE_WARNING("Invalid value '" + v.getParameter().getParameter("SAL", "-1") + "'for vehicle parameter 'SAL'");
            }

        } else {
          //  std::cout << "vehicle '" << v.getID() << "' does not supply vehicle parameter 'SAL'. Using default of " << customParameter2 << "\n";
        }
        // get custom vType parameter
        double customParameter3 = -1;
        if (v.getVehicleType().getParameter().knowsParameter("SAL")) {
            try {
                customParameter3 = TplConvert::_2double(v.getVehicleType().getParameter().getParameter("SAL", "-1").c_str());
            } catch (...) {
                WRITE_WARNING("Invalid value '" + v.getVehicleType().getParameter().getParameter("SAL", "-1") + "'for vType parameter 'SAL'");
            }

        } else {
           // std::cout << "vehicle '" << v.getID() << "' does not supply vType parameter 'SAL'. Using default of " << customParameter3 << "\n";
        }
        MSDevice_SAL* device = new MSDevice_SAL(v, "SAL_" + v.getID(),
                                                        oc.getFloat("device.SAL.parameter"),
                                                        customParameter2,
                                                        customParameter3);
        into.push_back(device);
    }
}


// ---------------------------------------------------------------------------
// MSDevice_SAL-methods
// ---------------------------------------------------------------------------
MSDevice_SAL::MSDevice_SAL(SUMOVehicle& holder, const std::string& id,
                                   double customValue1, double customValue2, double customValue3) :
        MSDevice(holder, id),
        myCustomValue1(customValue1),
        myCustomValue2(customValue2),
        myCustomValue3(customValue3) {
    //std::cout << "initialized device '" << id << "' with myCustomValue1=" << myCustomValue1 << ", myCustomValue2=" << myCustomValue2 << ", myCustomValue3=" << myCustomValue3 << "\n";
    MessengerSystem::getInstance().addNewMessengerAgent(holder.getID(), &myHolder, this);
}


MSDevice_SAL::~MSDevice_SAL() {
    if (!MSNet::getInstance()->closed)
            MessengerSystem::getInstance().removeMessengerAgent(myHolder.getID());
    delete myLCm;
}


bool
MSDevice_SAL::notifyMove(SUMOVehicle& veh, double /* oldPos */,
                             double /* newPos */, double newSpeed) {
    if (myLCm == nullptr) {
        myLCm = new LCManager((MSLCM_SmartSL2015*) &((MSVehicle *) (&myHolder))->getLaneChangeModel());
    }
    if (myLaneChangeModel == nullptr) myLaneChangeModel = (MSLCM_SmartSL2015*) &((MSVehicle *) (&myHolder))->getLaneChangeModel();
    MSLCM_SmartSL2015 &lcm = *myLaneChangeModel;

    if (entryMarkerFlag == 0 && veh.getEdge()->getID().length()>11 && (veh.getEdge()->getID()).compare(6,5,"Entry")==0) {
        MessagingProxy::getInstance().informEnterEntryMarker(veh.getID(),
                                                             (EntryMarker*)(MarkerSystem::getInstance().findMarkerByID(veh.getEdge()->getID())));
        myJudge = ((EntryMarker*)(MarkerSystem::getInstance().findMarkerByID(veh.getEdge()->getID())))->getJudge();
        if (!reported) myJudge->reportComing(MessagingProxy::getInstance().getGroupOf(myHolder.getID()), myDirection);
        reported = true;

    }
    if (entryMarkerFlag>=0) --entryMarkerFlag;

    myGroup = MessagingProxy::getInstance().getGroupOf(myHolder.getID());
    if (myGroup != nullptr) {
        bool debug = myHolder.isSelected();
        Position posi = myHolder.getPosition(0);
        double x = posi.x(),
            y = posi.y();
        double deltaX = sqrt( pow((myJudge->posX - x),2) + pow((myJudge->posY-y),2) );
        double speedLimit = myHolder.getLane()->getSpeedLimit();
        if (myGroup->groupLeader->mySAL != this) {
            if (myLeaderMessenger == nullptr) myLeaderMessenger = myGroup->getLeaderOf(MessagingProxy::getInstance().getMessenger(myHolder.getID()));
            //else return true;
            SUMOVehicle* myLeader = &myLeaderMessenger->mySAL->myHolder;

            Position position = myLeader->getPosition(0);
            double deltaS = sqrt(pow(position.x()-posi.x(), 2) + pow(position.y()-posi.y(),2));
            if (deltaS < -10) deltaS = 100;
            double desiredSpeed = deltaS > GROUP_GAP_DESIRED + GROUP_GAP_THRESHOLD? 25 :
                                         deltaS > GROUP_GAP_DESIRED - GROUP_GAP_THRESHOLD?
                                            myLeader->getSpeed()/(GROUP_GAP_DESIRED-GROUP_GAP_LIMIT)*(deltaS-GROUP_GAP_LIMIT):
                                            0;
            if (debug) std::cout << myHolder.getID() << "has following distance of: " << deltaS << std::endl
                        << " desired speed: " << desiredSpeed << std::endl <<
                        " lateral position: " << lcm.getCommittedSpeed() << std::endl;

            desiredSpeed = desiredSpeed<0? 0: desiredSpeed;


            if (desiredSpeed < speedLimit && (desiredSpeed < lcm.getCommittedSpeed() || lcm.getCommittedSpeed()<0.0001)) setVehicleSpeed(desiredSpeed);
        } else {
            myLeaderMessenger = nullptr;
            locked = true;
            if (reported && !inJunction) passPermitted = myJudge->canPass(this);
            locked = false;
            if (!passPermitted && !inJunction) {
                double desiredSpeed = speedLimit * ((deltaX - myJudge->stopRadius) / REPORT_DISTANCE);
                if (desiredSpeed < speedLimit) setVehicleSpeed(desiredSpeed);
                if (desiredSpeed <= 0) setVehicleSpeed(0);
                if (passPermitted) {
                    std::cout << myHolder.getID() << " is permitted to pass" << std::endl;
                } else if (debug)
                    std::cout << myHolder.getID() << ": "<<deltaX << "m, "<< desiredSpeed << std::endl;
            } else {
                    if (!(lcm.getOwnState() & LCA_STAY)) setVehicleSpeed(20); else {
                        if (debug) std::cout << "OKÉ" << std::endl;
                        if (!speedSetInJunction) {
                            speedSetInJunction = true;
                            setVehicleSpeed(25);
                        }
                    }

                    if (debug) std::cout << myHolder.getID() << "make full speed "<<
                                                         lcm.getCommittedSpeed() << std::endl;
            }
        }
        if (!inJunction && deltaX < myJudge->ponrRadius) {
            if (debug) std::cout << myHolder.getID() << "has passed PONR." << std::endl;
            myJudge->carPassedPONR(this);
            inJunction = true;
            speedSetInJunction = false;
        }
    } else myLeaderMessenger = nullptr;

    return true; // keep the device
}


bool
MSDevice_SAL::notifyEnter(SUMOVehicle& veh, MSMoveReminder::Notification reason, const MSLane* enteredLane) {

    //is it a marker?
    if(MarkerSystem::getInstance().isMarkerID(veh.getEdge()->getID())) {
        if ((veh.getEdge()->getID()).compare(6,5,"Entry")==0) {
            entryMarkerFlag = 2;
        }
        else if (inJunction){
            MessagingProxy::getInstance().informEnterExitMarker(veh.getID(),
                                                                (ExitMarker*)(MarkerSystem::getInstance().findMarkerByID(veh.getEdge()->getID())));
            myJudge->carLeftJunction(this);
            myLeaderMessenger = nullptr;
            inJunction=false;
            reported = false;
            speedSetInJunction = false;
        }
    }
    return true; // keep the device
}


bool
MSDevice_SAL::notifyLeave(SUMOVehicle& veh, double /*lastPos*/, MSMoveReminder::Notification reason, const MSLane* /* enteredLane */) {
    return true; // keep the device
}


void
MSDevice_SAL::generateOutput() const {
    if (OptionsCont::getOptions().isSet("tripinfo-output")) {
        OutputDevice& os = OutputDevice::getDeviceByOption("tripinfo-output");
        os.openTag("SAL_device");
        os.writeAttr("customValue1", toString(myCustomValue1));
        os.writeAttr("customValue2", toString(myCustomValue2));
        os.closeTag();
    }
}

std::string
MSDevice_SAL::getParameter(const std::string& key) const {
    if (key == "customValue1") {
        return toString(myCustomValue1);
    } else if (key == "customValue2") {
        return toString(myCustomValue2);
    } else if (key == "meaningOfLife") {
        return "42";
    }
    throw InvalidArgument("Parameter '" + key + "' is not supported for device of type '" + deviceName() + "'");
}


void
MSDevice_SAL::setParameter(const std::string& key, const std::string& value) {
    double doubleValue;
    try {
        doubleValue = TplConvert::_2double(value.c_str());
    } catch (NumberFormatException&) {
        throw InvalidArgument("Setting parameter '" + key + "' requires a number for device of type '" + deviceName() + "'");
    }
    if (key == "customValue1") {
        myCustomValue1 = doubleValue;
    } else {
        throw InvalidArgument("Setting parameter '" + key + "' is not supported for device of type '" + deviceName() + "'");
    }
}

void MSDevice_SAL::setVehicleColor(const libsumo::TraCIColor &color) {
    if (myHolder.isSelected()) {
        std::cout << "";
    }
    originalColor = libsumo::VehicleType::getColor(myHolder.getVehicleType().getID());
    libsumo::Vehicle::setColor(myHolder.getID(), color);
}

void MSDevice_SAL::resetVehicleColor() {
    libsumo::Vehicle::setColor(myHolder.getID(), originalColor);
}

void MSDevice_SAL::informBecomeLeader() {
    MSLCM_SmartSL2015 &lcm = (MSLCM_SmartSL2015&)((MSVehicle*)(&myHolder))->getLaneChangeModel();
    myLCm->setIsLeader();
    passPermitted = false;
    isMember = false;

}

void MSDevice_SAL::informNoLongerLeader() {
    MSLCM_SmartSL2015 &lcm = (MSLCM_SmartSL2015&)((MSVehicle*)(&myHolder))->getLaneChangeModel();
    myLCm->leaveGroup();
    followerFIFO.clear();
    isMember = false;
    inJunction = false;
}

void MSDevice_SAL::informBecomeMember(Group* group) {
    MSLCM_SmartSL2015 &lcm = (MSLCM_SmartSL2015&)((MSVehicle*)(&myHolder))->getLaneChangeModel();
    myLCm->setIsMember(group);
    followerFIFO.clear();
    isMember = true;
}

bool MSDevice_SAL::laneChanged(MSLCM_SmartSL2015 *follower, int offset) {
    bool isLast = MessagingProxy::getInstance().informLaneChange(myHolder.getID(), follower, offset);
    if (isLast) {
        myLCm -> groupChanged();
        Group* group = MessagingProxy::getInstance().getGroupOf(myHolder.getID());
        if (group->carIDs.size()!=0) group->carIDs.erase(group->carIDs.begin());
    }
    myLCm->changed();
    return isLast;
}

void MSDevice_SAL::laneChangeNeeded(MSLCM_SmartSL2015 *follower, int offset) {
    myLCm -> hasToChange(offset);
}

SUMOVehicle* MSDevice_SAL::getMyGroupLeader() {
    Group* group = MessagingProxy::getInstance().getGroupOf(myHolder.getID());
    return group != nullptr? &(group->groupLeader->mySAL->myHolder): nullptr;
}

double MSDevice_SAL::getGroupLength() {
    Group* group = MessagingProxy::getInstance().getGroupOf(myHolder.getID());
    return group != nullptr? group->getGroupLength() : libsumo::Vehicle::getLength(myHolder.getID());
}

void MSDevice_SAL::setVehicleSpeed(double speed) {
    libsumo::Vehicle::setSpeed(myHolder.getID(), speed);
}

void MSDevice_SAL::groupChanging(MSLCM_SmartSL2015 *follower) {
    myLCm->groupChanging(follower);
}


void MSDevice_SAL::amBlocker(MSLCM_SmartSL2015 *blocker, MSLCM_SmartSL2015 *leader) {
    Group* group = MessagingProxy::getInstance().getGroupOf(leader->getMyVehicle()->getID());
    if (group != nullptr) group->laneChange(blocker);
    else {
        MSDevice_SAL* otherDevice = static_cast<MSDevice_SAL*>(leader->getMyVehicle()->getDevice(typeid(MSDevice_SAL)));
        otherDevice->myLCm->groupChanging(blocker);
    }
    myLCm->blocker(blocker);
}

SUMOVehicle* MSDevice_SAL::getVehicle() {
    return &myHolder;
}

bool MSDevice_SAL::isFirst() {
    return (libsumo::Vehicle::getLeader(myHolder.getID(), STOP_DISTANCE)).second < 0;
}