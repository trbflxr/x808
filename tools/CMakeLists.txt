cmake_minimum_required(VERSION 3.10)
project(xe_tools)

set(CMAKE_CXX_STANDARD 17)

link_directories(${XE_DIRS})
include_directories(${XE_INCLUDE_DIRS})
include_directories(${XE_EXTERNAL_INCLUDE_DIRS})
include_directories(include)

#image to bin
set(I2B_SRC src/imgtobin/imgtobin.cpp)

add_executable(img_to_bin ${I2B_SRC})
target_link_libraries(img_to_bin freeimage)
target_compile_definitions(img_to_bin PRIVATE -DFREEIMAGE_LIB)


#spak
set(SPAK_SRC src/spak/spak.cpp)

#shared
add_library(spak SHARED ${SPAK_SRC})
target_link_libraries(spak libstdc++fs.a)

add_executable(spak_exec src/spak/main.cpp ${SPAK_SRC})
target_link_libraries(spak_exec libstdc++fs.a)
