cmake_minimum_required(VERSION 3.10)
project(lib-imgui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

file(GLOB IMGUI_SRC
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

add_library(imgui STATIC ${IMGUI_SRC})
