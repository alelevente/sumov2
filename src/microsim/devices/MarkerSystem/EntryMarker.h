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

/// @brief entry marker's answer to the incoming smart cars: list of exit markers
struct EntryMarkerAnswer{
    std::vector<ExitMarker*>* exitMarkers;
};

/// @brief This class implements the entry markers.
class EntryMarker: public BaseMarker{
public:
    /// @brief constructor
    EntryMarker(std::string markerID, MSEdge* position, const std::map<std::string, BaseMarker*>& markerMap);
    /// @brief destructor
    ~EntryMarker();

    /// @brief called when a smart car arrives at this entry marker. It returns the list of exit markers which can be reached from this entry marker
    void* onEnter(SUMOVehicle* who);
    /// @brief called when a smart car leaves this entry marker. Returns nullptr.
    void* onExit(SUMOVehicle* who);
    /// @brief list of exit markers which are reachable from this exit marker
    std::vector<ExitMarker*> exitMarkers;
    /// @brief getter of myJudge
    AbstractJudge* getJudge();
    /// @brief setter of myJudge
    void setJudge(AbstractJudge* judge);

private:
    /// @brief pointer to the intersection's judge
    AbstractJudge *myJudge;
};

#endif //SUMO_ENTRYMARKER_H