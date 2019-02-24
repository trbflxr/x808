cmake_minimum_required(VERSION 3.10)
project(xe_sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XE_DEBUG_FLAGS} -D S2D_DEBUG")

include_directories(${XE_INCLUDE_DIRS})
link_directories(${XE_STATIC_LIB_DIRS})

#sandbox
set(SANDBOX_SRC
        src/main.cpp
        src/test2d.cpp
        src/test3d.cpp
        src/testb2d.cpp
        src/testl2d.cpp
        src/testp2d.cpp
        src/debugui.cpp)

add_executable(sandbox ${SANDBOX_SRC})

target_link_libraries(sandbox xe)

#shaders
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pack001.pak")
    file(COPY pack001.pak DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else ()
    message(WARNING "You have to build shaders first using spak")
endif ()

#config
if (EXISTS "xeconfig")
    file(COPY xeconfig DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else ()
    file(WRITE xeconfig
            "width=1280\n"
            "height=720\n"
            "fullScreen=0\n"
            "vSync=0\n"
            "ups=30\n"
            "fps=0\n"
            "srgb=1\n"
            "renderApi=ogl\n"
            "apiVersion=430\n"
            "maxPointLights2D=50\n")

    file(COPY xeconfig DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

file(COPY xe_sandbox_assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
