//
// Created by levente on 2018.06.20..
//

#include <microsim/MSVehicle.h>
#include <microsim/devices/MarkerSystem/EntryMarker.h>
#include <libsumo/Vehicle.h>
#include "Messenger.h"
#include "MessengerSystem.h"

Messenger::Messenger(SUMOVehicle *myVech, MSDevice_SAL *mySAL) :
    myVehicle(myVech),
    mySAL(mySAL)
{
}

Messenger::~Messenger() {}

void Messenger::joinAGroup(EntryMarker &entryMarker) {
    if (myGroup != nullptr)
        return;
    MSVehicle* myVech = static_cast<MSVehicle*>(myVehicle);
    std::pair< const MSVehicle *const, double > vech = myVech->getLeader(MAX_DISTANCE);
    MSVehicle* other = const_cast<MSVehicle*>(vech.first);

    //find exit-marker:
    std::vector<ExitMarker *> *exitMarkers = static_cast< std::vector<ExitMarker *> *>(((EntryMarkerAnswer *) entryMarker.onEnter(
            myVehicle))->exitMarkers);
    ExitMarker *exitMarker = NULL;
    myExitMarker = nullptr;

    for (auto e: myVech->getRoute().getEdges()){
        for (auto m: *exitMarkers) {
            if (e->getID() == m->getMarkerID()) {
                myExitMarker = m;
                break;
            }
        }
        if (myExitMarker != nullptr) break;
    }
    if (myExitMarker == nullptr) {
        std::cout << "have not find at: " << entryMarker.getMarkerID() << std::endl;
        for (auto i = myVehicle->getRoute().begin(); i != myVehicle->getRoute().end(); ++i) {
            std::cout << "\t" << (*i)->getID() << std::endl;
        }
    }
    mySAL->myDirection = entryMarker.getMarkerID()+ "-"+myExitMarker->getMarkerID();

    //we can join:
    if (other != nullptr) {
        Messenger *otherAgent = MessengerSystem::getInstance().messengerMap[other->getID()];
        if (otherAgent != nullptr && otherAgent->myGroup != nullptr) {
            if (otherAgent->myGroup->canJoin && otherAgent->myExitMarker == myExitMarker) {
                otherAgent->myGroup->addNewMember(this);
                myGroup = otherAgent->myGroup;
                return;
            }
        }
    }

    //we cannot join:
    myGroup = new Group(this);
}

void Messenger::leaveGroup() {
    if (myGroup == nullptr) return;
    myGroup->removeCar(this);
    myGroup = nullptr;
    mySAL->resetVehicleColor();
}

Group* Messenger::getGroup() { return myGroup; }

void Messenger::needToChangeLane(MSLCM_SmartSL2015 *follower, int offset) {
    if (mySAL == nullptr ) return;
    try {

        mySAL->laneChangeNeeded(follower, offset);
    } catch (...) {

    }
}