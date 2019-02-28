cmake_minimum_required(VERSION 3.10)
project(xe_tools)

set(CMAKE_CXX_STANDARD 17)

include_directories(${XE_INCLUDE_DIRS})
include_directories(include)

#image to bin
set(I2B_SRC src/imgtobin/imgtobin.cpp)

add_executable(img_to_bin ${I2B_SRC})


#spak
set(SPAK_SRC
        src/spak/spak.cpp)

#shared
add_library(spk SHARED ${SPAK_SRC})
target_link_libraries(spk libstdc++fs.a)

#shader packer
add_executable(spak src/spak/spakmain.cpp ${SPAK_SRC})
target_link_libraries(spak libstdc++fs.a)
