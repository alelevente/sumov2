//
// Created by levente on 2018.03.10..
//

#ifndef SUMO_ENTRYMARKER_H
#define SUMO_ENTRYMARKER_H

#include <microsim/devices/Judge/AbstractJudge.h>
#include "BaseMarker.h"
#include "ExitMarker.h"
#include "microsim/devices/Judge/AbstractJudge.h"
#include "MarkerSystem.h"

class AbstractJudge;

struct EntryMarkerAnswer{
//    Judge* judge;
    std::vector<ExitMarker*>* exitMarkers;
};

class EntryMarker: public BaseMarker{
public:
    EntryMarker(std::string markerID, MSEdge* position, const std::map<std::string, BaseMarker*>& markerMap);
    ~EntryMarker();

    void* onEnter(SUMOVehicle* who);
    void* onExit(SUMOVehicle* who);
    std::vector<ExitMarker*> exitMarkers;
    AbstractJudge* getJudge();
    void setJudge(AbstractJudge* judge);

private:
    AbstractJudge *myJudge;
};

#endif //SUMO_ENTRYMARKER_H