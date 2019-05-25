cmake_minimum_required(VERSION 3.10)
project(xee)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D XEE_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${XE_RELEASE_FLAGS}")

include_directories(${XE_INCLUDE_DIRS})
link_directories(${XE_STATIC_LIB_DIRS})

file(GLOB XEE_SRC
        src/*.cpp)

add_executable(xee ${XEE_SRC})

target_link_libraries(xee xe)
