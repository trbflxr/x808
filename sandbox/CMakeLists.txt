cmake_minimum_required(VERSION 3.10)
project(xe_sandbox2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D S2D_DEBUG -D XE_DEBUG")

link_directories(${XE_DIRS})
include_directories(${XE_INCLUDE_DIRS})

#sandbox
set(S2D_SRC
        src/main.cpp
        src/test2d.cpp
        src/test3d.cpp
        src/debugui.cpp)

add_executable(sandbox2d ${S2D_SRC})

target_link_libraries(sandbox2d xe)