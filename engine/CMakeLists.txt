cmake_minimum_required(VERSION 3.10)
project(xe)


option(XE_PLATFORM_WIN32 "Win32" ON)
option(XE_PLATFORM_GL "OpenGL" ON)

set(XE_DEBUG_FLAGS "-D XE_DEBUG -Wall -Wno-unused-function -Wno-class-memaccess"
        CACHE STRING "xe_debug defines, compile options")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS}")

add_definitions(
        -D NOGDI
        -D UNICODE
        -D XE_STATIC
        -D GLEW_STATIC)

#external libs
add_subdirectory(external/box2d)
include_directories(external/box2d)

add_subdirectory(external/freetype-gl)
include_directories(external/freetype-gl/include)

#includes and libs
include_directories(src)
link_directories(${XE_DIRS})
include_directories(${XE_INCLUDE_DIRS})
include_directories(${XE_EXTERNAL_INCLUDE_DIRS})

#engine
file(GLOB ENGINE_SRC
        src/app/*.cpp
        src/ecs/*.cpp
        src/ecs/components/*.cpp
        src/ecs/systems/*.cpp
        src/embedded/*.cpp
        src/gfx/2d/*.cpp
        src/gfx/platform/*.cpp
        src/gfx/camera/*.cpp
        src/gfx/fx/*.cpp
        src/gfx/layers/*.cpp
        src/gfx/lights/*.cpp
        src/gfx/*.cpp
        src/loaders/*.cpp
        src/math/*.cpp
        src/physics/2d/*.cpp
        src/objects/*.cpp
        src/resources/*.cpp
        src/systems/*.cpp
        src/utils/*.cpp
        src/window/*.cpp
        src/*.cpp)


#win32
file(GLOB ENGINE_WIN32_SRC
        src/utils/platform/win32/*.cpp
        src/window/platform/win32/*.cpp)

#opengl
file(GLOB ENGINE_GL_SRC
        external/glew/glew.c
        src/gfx/platform/opengl/*.cpp)

#total platform files
file(GLOB PLATFORM_SRC)

if (XE_PLATFORM_WIN32)
    list(APPEND PLATFORM_SRC ${ENGINE_WIN32_SRC})
endif ()

if (XE_PLATFORM_GL)
    find_package(OpenGL REQUIRED)
    list(APPEND PLATFORM_SRC ${ENGINE_GL_SRC})
endif ()


#xe lib
add_library(xe SHARED ${PLATFORM_SRC} ${ENGINE_SRC})

target_link_libraries(xe
        spak
        freetype-gl freetype bz2 png libz
        assimp irrxml
        gorilla openal32
        box2d)

#link opengl libs
if (XE_PLATFORM_GL)
    target_link_libraries(xe ${OPENGL_LIBRARIES})
endif ()

#link win32 libs
if (XE_PLATFORM_WIN32)
    target_link_libraries(xe winmm)
endif ()
