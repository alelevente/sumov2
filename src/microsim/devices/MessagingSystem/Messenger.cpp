//
// Created by levente on 2018.06.20..
//

#include <microsim/MSVehicle.h>
#include <microsim/devices/MarkerSystem/EntryMarker.h>
#include "Messenger.h"
#include "MessengerSystem.h"

Messenger::Messenger(SUMOVehicle *myVech, MSDevice_SAL *mySAL) :
    myVehicle(myVech),
    mySAL(mySAL)
{
}

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
    //actualJudge = ((EntryMarkerAnswer*)result)->judge;
    for (auto i = exitMarkers->begin(); i != exitMarkers->end(); ++i) {
        if (myVehicle->getRoute().contains((*i)->getPosition())) {
            myExitMarker = *i;
        }
    }

    //we can join:
    if (other != nullptr) {
        Messenger *otherAgent = MessengerSystem::getInstance().messengerMap[other->getID()];
        if (otherAgent != nullptr) {
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
    myGroup->removeFirstCar();
    myGroup = nullptr;
}