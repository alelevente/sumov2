set(microsim_devices_STAT_SRCS
   MSDevice.cpp
   MSDevice.h
   MSDevice_SSM.cpp
   MSDevice_SSM.h
   MSDevice_ToC.cpp
   MSDevice_ToC.h
   MSDevice_BTreceiver.cpp
   MSDevice_BTreceiver.h
   MSDevice_BTsender.cpp
   MSDevice_BTsender.h
   MSDevice_Emissions.cpp
   MSDevice_Emissions.h
   MSDevice_Transportable.cpp
   MSDevice_Transportable.h
   MSDevice_Routing.cpp
   MSDevice_Routing.h
   MSDevice_Tripinfo.cpp
   MSDevice_Tripinfo.h
   MSDevice_Battery.cpp
   MSDevice_Battery.h
   MSDevice_Example.cpp
   MSDevice_Example.h
   MSDevice_Vehroutes.cpp
   MSDevice_Vehroutes.h
   MSDevice_Bluelight.cpp
   MSDevice_Bluelight.h
   MSDevice_FCD.cpp
   MSDevice_FCD.h
        MSDevice_SAL.h MSDevice_SAL.cpp MarkerSystem/MarkerSystem.cpp MarkerSystem/MarkerSystem.h MarkerSystem/BaseMarker.cpp MarkerSystem/BaseMarker.h MarkerSystem/EntryMarker.cpp MarkerSystem/EntryMarker.h MarkerSystem/ExitMarker.cpp MarkerSystem/ExitMarker.h MessagingSystem/MessagingProxy.cpp MessagingSystem/MessagingProxy.h MessagingSystem/MessengerSystem.cpp MessagingSystem/MessengerSystem.h MessagingSystem/Messenger.cpp MessagingSystem/Messenger.h GroupingSystem/Group.cpp GroupingSystem/Group.h Others/Helper.cpp Others/Helper.h)

add_library(microsim_devices STATIC ${microsim_devices_STAT_SRCS} MSDevice_SAL.h MSDevice_SAL.cpp MarkerSystem/MarkerSystem.cpp MarkerSystem/MarkerSystem.h MarkerSystem/BaseMarker.cpp MarkerSystem/BaseMarker.h MarkerSystem/EntryMarker.cpp MarkerSystem/EntryMarker.h MessagingSystem/MessagingProxy.cpp MessagingSystem/MessagingProxy.h)
set_property(TARGET microsim_devices PROPERTY PROJECT_LABEL "z_microsim_devices")
