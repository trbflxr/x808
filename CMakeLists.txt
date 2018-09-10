cmake_minimum_required(VERSION 3.10)
project(x808)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#directories
set(XE_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
        CACHE STRING "XE include dirs" FORCE)

set(XE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freeimage/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-gl/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/gorilla-audio/lib
        CACHE STRING "XE library dirs" FORCE)

set(XE_EXTERNAL_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freeimage/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-gl/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/gorilla-audio/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/json/include
        CACHE STRING "XE external include dirs" FORCE)

file(COPY
        assets
        xeconfig
        pack001.pak

        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(engine)
add_subdirectory(sandbox)
add_subdirectory(editor)
add_subdirectory(tools)