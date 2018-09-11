cmake_minimum_required(VERSION 3.10)
project(box2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

file(GLOB B2D_SRC
        Box2D/Collision/*.cpp
        Box2D/Collision/Shapes/*.cpp
        Box2D/Common/*.cpp
        Box2D/Dynamics/*.cpp
        Box2D/Dynamics/Contacts/*.cpp
        Box2D/Dynamics/Joints/*.cpp
        Box2D/Rope/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(box2d STATIC ${B2D_SRC})
