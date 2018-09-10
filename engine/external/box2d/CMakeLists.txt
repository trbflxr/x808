cmake_minimum_required(VERSION 3.10)
project(box2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

file(GLOB B2D_SRC
        box2d/Collision/*.cpp
        box2d/Collision/Shapes/*.cpp
        box2d/Common/*.cpp
        box2d/Dynamics/*.cpp
        box2d/Dynamics/Contacts/*.cpp
        box2d/Dynamics/Joints/*.cpp
        box2d/Rope/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(box2d STATIC ${B2D_SRC})
