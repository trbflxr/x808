cmake_minimum_required(VERSION 3.10)
project(xee)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D XEE_DEBUG")

link_directories(${XE_DIRS})
include_directories(${XE_INCLUDE_DIRS})
include_directories(${XE_EXTERNAL_INCLUDE_DIRS})

include_directories(imgui)

#sandbox
file(GLOB XEE_SRC
        imgui/*.cpp
        src/*.cpp)

add_executable(xee ${XEE_SRC})

target_link_libraries(xee xe)