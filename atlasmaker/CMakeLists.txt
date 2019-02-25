cmake_minimum_required(VERSION 3.10)
project(xe_atlas_maker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D XEAM_DEBUG")

include_directories(${XE_INCLUDE_DIRS})
link_directories(${XE_STATIC_LIB_DIRS})


file(GLOB SRC
        src/*.cpp)

add_executable(atlasmkr ${SRC})

target_link_libraries(atlasmkr xe)
