//
// Created by levente on 2018.03.10..
//

#ifndef SUMO_EXITMARKER_H
#define SUMO_EXITMARKER_H

#include "BaseMarker.h"

/// @brief This class implements exit markers.
class ExitMarker: public BaseMarker{
public:
    /// @brief constructor
    ExitMarker(std::string markerID, MSEdge* position);
    /// @brief destructor
    ~ExitMarker();

    /// @brief called if a smart car arrives at this exit marker. Always return null
    void* onEnter(SUMOVehicle* who);
    /// @brief called if a smart car left this exit marker. Returns this
    void* onExit(SUMOVehicle* who);
};


#endif //SUMO_EXITMARKER_H