cmake_minimum_required(VERSION 3.10)
project(lib-freetype-gl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

file(GLOB FTGL_SRC
        src/*.c)

include_directories(include/freetype-gl)
include_directories(include/freetype-gl/freetype)

add_library(freetype-gl STATIC ${FTGL_SRC})
