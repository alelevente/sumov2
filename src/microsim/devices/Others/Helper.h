//
// Created by levente on 2018.06.22..
//

#ifndef SUMO_HELPER_H
#define SUMO_HELPER_H


#include <microsim/devices/MSDevice_SAL.h>

class Helper {
public:
    static inline MSDevice_SAL* getSALFromVehicle(SUMOVehicle *vehicle);
};


#endif //SUMO_HELPER_H
