cmake_minimum_required(VERSION 3.10)
project(xe_sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D S2D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${XE_RELEASE_FLAGS}")

include_directories(${XE_INCLUDE_DIRS})
include_directories(src)
link_directories(${XE_STATIC_LIB_DIRS})

#sandbox
file(GLOB SANDBOX_SRC
        src/*.cpp
        src/2d/*.cpp
        src/2d/0/*.cpp
        src/2d/1/*.cpp
        src/2d/2/*.cpp
        src/2d/3/*.cpp
        src/2d/4/*.cpp
        src/3d/*.cpp)

add_executable(sandbox ${SANDBOX_SRC})

target_link_libraries(sandbox xe)

#shaders
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pack001.pak")
    file(COPY pack001.pak DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else ()
    message(WARNING "You have to build shaders first using spak")
endif ()

#config
if (EXISTS "xeconfig")
    file(COPY xeconfig DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else ()
    file(WRITE xeconfig
            "width=1280\n"
            "height=720\n"
            "//0-window 1-borderless 2-fullscreen\n"
            "fullScreen=0\n"
            "vSync=0\n"
            "maxFps=0\n"
            "tickRate=60\n"
            "srgb=1\n"
            "renderApi=ogl\n"
            "apiVersion=330\n"
            "maxSpotShadows=4\n"
            "maxDirectionalCascades=4\n"
            "shadowQuality=3 //0-3\n")

    file(COPY xeconfig DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

file(COPY xe_sandbox_assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
