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
        external/glew/src/glew.c

        src/application/window.cpp
        src/application/input.cpp
        src/application/application.cpp

        src/gfx/api/context.cpp
        src/gfx/api/vertexbuffer.cpp
        src/gfx/api/indexbuffer.cpp
        src/gfx/api/vertexarray.cpp
        src/gfx/api/shader.cpp
        src/gfx/api/texture.cpp
        src/gfx/api/texture2d.cpp
        src/gfx/layers/layer2d.cpp
        src/gfx/camera/camera.hpp
        src/gfx/renderer.cpp
        src/gfx/renderer2d.cpp
        src/gfx/renderer2d.hpp
        src/gfx/renderable2d.cpp

        src/math/vec2.cpp
        src/math/vec3.cpp
        src/math/vec4.cpp
        src/math/mat4.cpp
        src/math/quat.cpp
        src/math/rect.cpp
        src/math/aabb.cpp
        src/math/aobb.cpp

        src/objects/transform.cpp
        src/objects/gameobject.cpp
        src/gfx/sprite.cpp

        src/utils/log.cpp
        src/utils/timer.cpp
        src/utils/loadimage.cpp

        src/config.cpp

        #todo: remove
        src/gfx/api/basicshader.cpp)


add_library(xe SHARED ${ENGINE_SRC})

target_link_libraries(xe
        glew
        ${OPENGL_LIBRARIES}
        freeimage)