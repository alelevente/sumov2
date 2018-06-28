//
// Created by levente on 2018.06.20..
//

// ===========================================================================
// included modules
// ===========================================================================
#include <config.h>

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
            std::cout << "vehicle '" << v.getID() << "' does not supply vehicle parameter 'SAL'. Using default of " << customParameter2 << "\n";
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
            std::cout << "vehicle '" << v.getID() << "' does not supply vType parameter 'SAL'. Using default of " << customParameter3 << "\n";
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
    std::cout << "initialized device '" << id << "' with myCustomValue1=" << myCustomValue1 << ", myCustomValue2=" << myCustomValue2 << ", myCustomValue3=" << myCustomValue3 << "\n";
    MessengerSystem::getInstance().addNewMessengerAgent(holder.getID(), &myHolder, this);
}


MSDevice_SAL::~MSDevice_SAL() {
}


bool
MSDevice_SAL::notifyMove(SUMOVehicle& veh, double /* oldPos */,
                             double /* newPos */, double newSpeed) {
    //std::cout << "device '" << getID() << "' notifyMove: newSpeed=" << newSpeed << "\n";
    // check whether another device is present on the vehicle:
    MSDevice_Tripinfo* otherDevice = static_cast<MSDevice_Tripinfo*>(veh.getDevice(typeid(MSDevice_Tripinfo)));
    if (otherDevice != 0) {
        std::cout << "  veh '" << veh.getID() << " has device '" << otherDevice->getID() << "'\n";
    }

    if (entryMarkerFlag == 0 && (veh.getEdge()->getID()).compare(6,5,"Entry")==0) {
        MessagingProxy::getInstance().informEnterEntryMarker(veh.getID(),
                                                             (EntryMarker*)(MarkerSystem::getInstance().findMarkerByID(veh.getEdge()->getID())));
    }
    if (entryMarkerFlag>=0) --entryMarkerFlag;

    return true; // keep the device
}


bool
MSDevice_SAL::notifyEnter(SUMOVehicle& veh, MSMoveReminder::Notification reason, const MSLane* enteredLane) {
    //std::cout << "device '" << getID() << "' notifyEnter: reason=" << reason << " currentEdge=" << veh.getEdge()->getID() << "\n";

    //is it a marker?
    if(MarkerSystem::isMarkerID(veh.getEdge()->getID())) {
        if ((veh.getEdge()->getID()).compare(6,5,"Entry")==0)
            entryMarkerFlag = 2;
        else MessagingProxy::getInstance().informEnterExitMarker(veh.getID(),
                                                                  (ExitMarker*)(MarkerSystem::getInstance().findMarkerByID(veh.getEdge()->getID())));
    }
    return true; // keep the device
}


bool
MSDevice_SAL::notifyLeave(SUMOVehicle& veh, double /*lastPos*/, MSMoveReminder::Notification reason, const MSLane* /* enteredLane */) {
    //std::cout << "device '" << getID() << "' notifyLeave: reason=" << reason << " currentEdge=" << veh.getEdge()->getID() << "\n";
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
    originalColor = libsumo::VehicleType::getColor(myHolder.getVehicleType().getID());
    libsumo::Vehicle::setColor(myHolder.getID(), color);
}

void MSDevice_SAL::resetVehicleColor() {
    libsumo::Vehicle::setColor(myHolder.getID(), originalColor);
}

void MSDevice_SAL::informBecomeLeader() {}
void MSDevice_SAL::informNoLongerLeader() {}
void MSDevice_SAL::informBecomeMember() {}