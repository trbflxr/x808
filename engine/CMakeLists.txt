cmake_minimum_required(VERSION 3.10)
project(xe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

add_definitions(
        -D NOGDI
        -D XE_STATIC
        -D FREEIMAGE_LIB
        -D GLEW_STATIC)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D XE_DEBUG")

find_package(OpenGL REQUIRED)

include_directories(src)

#freeimage
include_directories(external/freeimage/include)
link_directories(external/freeimage/lib)

#glew
include_directories(external/glew/include)

#engine
set(ENGINE_SRC
        external/glew/src/glew.c)


add_library(xe SHARED ${ENGINE_SRC})

target_link_libraries(xe
        glew
        ${OPENGL_LIBRARIES}
        freeimage)