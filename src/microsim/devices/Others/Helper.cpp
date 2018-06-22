//
// Created by levente on 2018.06.22..
//

#include "Helper.h"
#include <utils/vehicle/SUMOVehicle.h>

MSDevice_SAL* Helper::getSALFromVehicle(SUMOVehicle *vehicle) {
    if (vehicle == NULL) return NULL;
    SUMOVehicle& veh = *(vehicle);
    return static_cast<MSDevice_SAL*>(veh.getDevice(typeid(MSDevice_SAL)));
}