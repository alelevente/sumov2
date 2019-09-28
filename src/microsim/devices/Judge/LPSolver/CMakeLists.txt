project(LPSolver)


add_library(LPSolver STATIC LPSolver.h LPSolver.cpp)

target_include_directories(LPSolver BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ortools/include)
target_link_libraries(LPSolver ${CMAKE_CURRENT_SOURCE_DIR}/ortools/lib/libortools.so)
target_link_directories(LPSolver BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ortools/objs)
target_link_libraries(LPSolver)



set_property(TARGET LPSolver PROPERTY PROJECT_LABEL "z_microsim_devices_lpsolver")


