project(PARTICLE_FILTER)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(sources
    src/Coordinate2D.hpp
    src/FixedSizeVector.hpp
    src/Landmark.cpp
    src/LandmarkAssociation.cpp
    src/LandmarkMap.hpp
    src/Landmarks.hpp
    src/MeanParticle.cpp
    src/MotionModel.cpp
    src/Observations.hpp
    src/Particle.cpp
    src/ParticleFilter.cpp
    src/StandardDeviationPosition.cpp
    src/StandardDeviationLandmark.cpp
    src/helper_functions.h
    src/json.hpp
    src/main.cpp
    )


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl/include)
link_directories(/usr/local/lib)
link_directories(/usr/local/opt/openssl/lib)
link_directories(/usr/local/Cellar/libuv/1*/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 


add_executable(particle_filter ${sources})
find_library(WS_LIB uWS HINTS ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(particle_filter z ssl uv "${WS_LIB}")
target_include_directories(particle_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

