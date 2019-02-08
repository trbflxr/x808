cmake_minimum_required(VERSION 3.10)
project(xe_sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D S2D_DEBUG")

include_directories(${XE_INCLUDE_DIRS})
link_directories(${XE_STATIC_LIB_DIRS})

#sandbox
set(SANDBOX_SRC
        src/main.cpp
        src/test2d.cpp
        src/test3d.cpp
        src/testb2d.cpp
        src/testl2d.cpp
        src/debugui.cpp)

add_executable(sandbox ${SANDBOX_SRC})

target_link_libraries(sandbox xe)

file(COPY
        xe_sandbox_assets
        xeconfig
        pack001.pak

        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
