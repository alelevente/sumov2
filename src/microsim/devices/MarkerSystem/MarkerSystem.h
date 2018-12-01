//
// Created by levente on 2018.03.10..
//

#ifndef SUMO_MARKERSYSTEM_H
#define SUMO_MARKERSYSTEM_H

#include <vector>
#include <string>
#include <map>
#include "BaseMarker.h"
#include "ExitMarker.h"

/// @brief This singleton class is responsible for the administration of every kind of markers.
class MarkerSystem{
    //singleton, so the following functions are private:
    MarkerSystem();
    ~MarkerSystem();
    MarkerSystem(MarkerSystem const&);
    void operator=(const MarkerSystem&);

    /// @brief list of markers
    std::map<std::string, BaseMarker*> markerMap;
    /// @brief this function connects exit markers and entry markers of intersections
    std::vector<ExitMarker*> findExitMarkerstoEntry(const std::string& entryID);

public:
    /// @brief for access the this singleton class
    static MarkerSystem& getInstance();
    /**
     * @brief Searches for a given marker by its name
     * @param ID The marker's name
     * @return pointer to the marker
     */
    BaseMarker* findMarkerByID(const std::string& ID);
    /// @brief helper function which returns true if the given string can be used as a marker's ID.
    bool isMarkerID(const std::string& ID);
    /// @brief helper function which can extract an intersection's name from a marker's ID
    std::string getJunctionName(const std::string& ID);
};

#endif //SUMO_MARKERSYSTEM_H