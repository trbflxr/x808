cmake_minimum_required(VERSION 3.10)
project(lib-glew)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")

find_package(OpenGL REQUIRED)

add_definitions(-D GLEW_STATIC)

file(GLOB GLEW_SRC
        glew.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(glew SHARED ${GLEW_SRC})

target_link_libraries(glew ${OPENGL_LIBRARIES})
