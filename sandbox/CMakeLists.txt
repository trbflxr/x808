cmake_minimum_required(VERSION 3.10)
project(xe_sandbox2d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D S2D_DEBUG -D XE_DEBUG")


link_directories(../engine/external/freeimage/lib)
link_directories(../engine/external/gorilla-audio/lib)


include_directories(../engine/src)

#sandbox
set(S2D_SRC
        src/main.cpp
        src/testecs.cpp
        src/test3d.cpp
        src/testui.cpp)

add_executable(sandbox2d ${S2D_SRC})

target_link_libraries(sandbox2d xe)