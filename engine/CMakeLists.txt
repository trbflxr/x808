cmake_minimum_required(VERSION 3.10)
project(xe)


option(XE_PLATFORM_WIN32 "Win32" ON)
option(XE_PLATFORM_GL "OpenGL" ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

add_definitions(
        -D NOGDI
        -D XE_STATIC
        -D FREEIMAGE_LIB
        -D GLEW_STATIC)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D XE_DEBUG")

include_directories(src)

#opengl
find_package(OpenGL REQUIRED)
link_libraries(${OPENGL_LIBRARIES})

#glew
include_directories(external/glew/include)

#freeimage
include_directories(external/freeimage/include)
link_directories(external/freeimage/lib)
link_libraries(freeimage)

#freetype-gl
include_directories(external/freetype-gl/include)
link_directories(external/freetype-gl/lib)
link_libraries(freetype-gl freetype bz2)

#gorilla-audio
include_directories(external/gorilla-audio/include)
link_directories(external/gorilla-audio/lib)
link_libraries(gorilla openal32)

#engine
file(GLOB ENGINE_SRC
        external/glew/src/glew.c

        embedded/embedded.cpp

        src/application/*.cpp
        src/ecs/*.cpp
        src/events/*.cpp
        src/gfx/api/*.cpp
        src/gfx/camera/*.cpp
        src/gfx/layers/*.cpp
        src/gfx/*.cpp
        src/math/*.cpp
        src/objects/*.cpp
        src/resources/*.cpp
        src/utils/*.cpp
        src/*.cpp)


#win32
file(GLOB ENGINE_WIN32_SRC src/platform/win32/*.cpp)

#opengl
file(GLOB ENGINE_GL_SRC src/platform/opengl/*.cpp)


#total platform files
file(GLOB PLATFORM_SRC)

if (XE_PLATFORM_WIN32)
    list(APPEND PLATFORM_SRC ${ENGINE_WIN32_SRC})
endif ()

if (XE_PLATFORM_GL)
    list(APPEND PLATFORM_SRC ${ENGINE_GL_SRC})
endif ()

add_library(xe SHARED ${PLATFORM_SRC} ${ENGINE_SRC})