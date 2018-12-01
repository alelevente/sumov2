//
// Created by levente on 2018.03.10..
//

#ifndef SUMO_BASEMARKER_H
#define SUMO_BASEMARKER_H


#include <microsim/MSEdge.h>

/// @brief Abstract base class for markers
class BaseMarker{
    /// @brief pointer to the edge where this marker is located
    MSEdge *position;
    /// @brief name of the marker
    std::string markerID;

    /// @brief cannot be compared
    bool operator= (const BaseMarker& rhs);
    /// @brief no copy ctor
    BaseMarker(const BaseMarker& rhs);

public:
    /// @brief getter of position
    MSEdge* getPosition();
    /// @brief setter of position
    void setPosition(MSEdge* posi);
    /// @brief getter of markerID
    std::string getMarkerID();

    /// @brief constructor
    BaseMarker(std::string markerID, MSEdge* position );
    /// @brief destructor
    ~BaseMarker();

    /**
     * @brief Called if a smart car has stepped on the marker.
     * @param who The incoming vehicle.
     * @return Anything important.
     */
    virtual void* onEnter(SUMOVehicle* who) = 0;
    virtual void* onExit(SUMOVehicle* who) = 0;
};
#endif //SUMO_BASEMARKER_H