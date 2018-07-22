cmake_minimum_required(VERSION 3.10)
project(xe_tools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

add_definitions(
        -D FREEIMAGE_LIB)

include_directories(../engine/external/freeimage/include)
link_directories(../engine/external/freeimage/lib)
link_libraries(freeimage)

set(SRC
        src/imgtobin.cpp)

add_executable(img_to_bin ${SRC})

target_link_libraries(img_to_bin freeimage)