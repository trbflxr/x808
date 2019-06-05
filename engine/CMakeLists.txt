cmake_minimum_required(VERSION 2.8)
project(xe)

macro(xe_set_option var default type docstring)
    if (NOT DEFINED ${var})
        set(${var} ${default})
    endif ()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

xe_set_option(XE_BUILD_SHARED_LIB TRUE BOOL "Build shared lib")
xe_set_option(XE_PLATFORM_WIN32 TRUE BOOL "Win32")
xe_set_option(XE_PLATFORM_GL TRUE BOOL "OpenGL")
xe_set_option(XE_USE_GENERIC_FS TRUE BOOL "Generic filesystem")

set(XE_DEBUG_FLAGS "-D XE_DEBUG -Wall -Wno-unused-function -Wno-class-memaccess"
        CACHE STRING "xe_debug defines, compile options")

set(XE_RELEASE_FLAGS "-D NDEBUG" CACHE STRING "xe_release defines, compile options")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${XE_RELEASE_FLAGS}")

set(XE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d
        CACHE STRING "XE include dirs" FORCE)

set(XE_STATIC_LIB_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/external/static/libs-mingw/x64 #todo: platform
        CACHE STRING "XE static lib dirs" FORCE)

set(XE_STATIC_LIB_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/external/static/include
        CACHE STRING "XE static lib include dirs" FORCE)

add_definitions(
        -D NOGDI
        -D UNICODE
        -D _UNICODE
        -D XE_STATIC)

if (XE_USE_GENERIC_FS)
    add_definitions(-D XE_USE_GENERIC_FS)
endif ()

#external libs
add_subdirectory(external/box2d)
include_directories(external/box2d)

add_subdirectory(external/glew)
include_directories(external/glew)

add_subdirectory(external/freetype-gl)
include_directories(external/freetype-gl/include)

include_directories(external/stb)
include_directories(external/dirent)

#static
include_directories(${XE_STATIC_LIB_INCLUDE_DIRS})
link_directories(${XE_STATIC_LIB_DIRS})

#tools
add_subdirectory(tools)
include_directories(tools/include)


#includes
include_directories(${XE_INCLUDE_DIRS})
include_directories(src)

#engine
file(GLOB ENGINE_SRC
        src/animation/*.cpp
        src/app/*.cpp
        src/audio/*.cpp
        src/core/*.cpp
        src/ecs/*.cpp
        src/ecs/components/*.cpp
        src/ecs/systems/*.cpp
        src/embedded/*.cpp
        src/gfx/2d/*.cpp
        src/gfx/fx/*.cpp
        src/gfx/particles/*.cpp
        src/gfx/platform/*.cpp
        src/gfx/camera/*.cpp
        src/gfx/layers/*.cpp
        src/gfx/lights/*.cpp
        src/gfx/*.cpp
        src/loaders/*.cpp
        src/math/*.cpp
        src/physics/2d/*.cpp
        src/objects/*.cpp
        src/resources/*.cpp
        src/systems/*.cpp
        src/timeline/*.cpp
        src/ui/imgui/*.cpp
        src/utils/*.cpp
        src/window/*.cpp
        src/*.cpp)


#win32
file(GLOB ENGINE_WIN32_SRC
        src/core/platform/win32/*.cpp
        src/utils/platform/win32/*.cpp
        src/window/platform/win32/*.cpp)

#opengl
file(GLOB ENGINE_GL_SRC
        src/ui/platform/opengl/*.cpp
        src/gfx/platform/opengl/*.cpp)

#total platform files
file(GLOB PLATFORM_SRC)

if (XE_PLATFORM_WIN32)
    list(APPEND PLATFORM_SRC ${ENGINE_WIN32_SRC})
endif ()

if (XE_PLATFORM_GL)
    list(APPEND PLATFORM_SRC ${ENGINE_GL_SRC})
endif ()


#xe lib
if (XE_BUILD_SHARED_LIB)
    add_library(xe SHARED ${PLATFORM_SRC} ${ENGINE_SRC})
else ()
    add_library(xe STATIC ${PLATFORM_SRC} ${ENGINE_SRC})
endif ()


target_link_libraries(xe
        spk
        openal32
        freetype-gl freetype bz2 png libz
        assimp irrxml
        box2d
        glew)

#link opengl libs
if (XE_PLATFORM_GL)
    target_link_libraries(xe glew)
endif ()

#link win32 libs
if (XE_PLATFORM_WIN32)
    target_link_libraries(xe winmm)
endif ()
