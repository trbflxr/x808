cmake_minimum_required(VERSION 3.10)
project(xe)


option(XE_PLATFORM_WIN32 "Win32" ON)
option(XE_PLATFORM_GL "OpenGL" ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D XE_DEBUG")

add_definitions(
        -D NOGDI
        -D UNICODE
        -D XE_STATIC
        -D FREEIMAGE_LIB
        -D GLEW_STATIC)

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
        src/objects/*.cpp
        src/resources/*.cpp
        src/utils/*.cpp
        src/window/*.cpp
        src/*.cpp)


#win32
file(GLOB ENGINE_WIN32_SRC
        src/utils/platform/win32/*.cpp
        src/window/platform/win32/*.cpp)

#opengl
file(GLOB ENGINE_GL_SRC
        src/gfx/platform/opengl/*.c
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
        freeimage
        assimp irrxml
        freetype-gl freetype bz2
        gorilla openal32)

#link opengl libs
if (XE_PLATFORM_GL)
    target_link_libraries(xe ${OPENGL_LIBRARIES})
endif ()

#link win32 libs
if (XE_PLATFORM_WIN32)
    target_link_libraries(xe winmm)
endif ()