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


#directories
set(XE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        CACHE STRING "XE include dirs" FORCE)

set(XE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freeimage/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-gl/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/gorilla-audio/lib
        CACHE STRING "XE library dirs" FORCE)

set(XE_EXTERNAL_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freeimage/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-gl/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/gorilla-audio/include)

link_directories(${XE_DIRS})
include_directories(${XE_INCLUDE_DIRS})
include_directories(${XE_EXTERNAL_INCLUDE_DIRS})

#engine
file(GLOB ENGINE_SRC
        src/application/*.cpp
        src/ecs/*.cpp
        src/ecs/components/*.cpp
        src/ecs/systems/*.cpp
        src/embedded/*.cpp
        src/gfx/api/*.cpp
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
        src/world/*.cpp
        src/world/lights/*.cpp
        src/world/model/*.cpp
        src/*.cpp)


#win32
file(GLOB ENGINE_WIN32_SRC
        src/platform/win32/*.cpp)

#opengl
file(GLOB ENGINE_GL_SRC
        src/platform/opengl/*.cpp
        src/platform/opengl/*.c)

#sse
file(GLOB ENGINE_SSE_SRC
        src/platform/sse/*.cpp)

#total platform files
file(GLOB PLATFORM_SRC)

if (XE_PLATFORM_WIN32)
    list(APPEND PLATFORM_SRC ${ENGINE_WIN32_SRC})
endif ()

if (XE_PLATFORM_GL)
    find_package(OpenGL REQUIRED)
    list(APPEND PLATFORM_SRC ${ENGINE_GL_SRC})
endif ()

#append sse platform
list(APPEND PLATFORM_SRC ${ENGINE_SSE_SRC})


#xe lib
add_library(xe SHARED ${PLATFORM_SRC} ${ENGINE_SRC})

target_link_libraries(xe
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