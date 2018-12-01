//
// Created by levente on 2018.03.11..
//

#include <utils/vehicle/SUMOVehicle.h>
#include "EntryMarker.h"
#include "MarkerSystem.h"

std::string getJunctionName(const std::string& markerId){
    int i;
    std::string str;
    for (i = 0; markerId[i]!='_'; ++i);
    ++i;
    while (markerId[i]!='_') {
        str += markerId[i];
        ++i;
    }
    return str;
}

void* EntryMarker::onEnter(SUMOVehicle *who) {
    EntryMarkerAnswer* answer = new EntryMarkerAnswer();
    answer->exitMarkers = &exitMarkers;
    return answer;
}

void* EntryMarker::onExit(SUMOVehicle *who) {
    return NULL;
}

EntryMarker::EntryMarker(std::string markerID, MSEdge *position, const std::map<std::string, BaseMarker*>& markerMap):
        BaseMarker(markerID, position)
{
    std::string junctionName = getJunctionName(markerID);
}

AbstractJudge* EntryMarker::getJudge(){
    return myJudge;
}

void EntryMarker::setJudge(AbstractJudge *judge) {
    myJudge = judge;
}