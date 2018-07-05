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
link_libraries(freeimage)

#freetype-gl
include_directories(external/freetype-gl/include)
link_directories(external/freetype-gl/lib)
link_libraries(freetype-gl freetype bz2)

#glew
include_directories(external/glew/include)
link_libraries(glew ${OPENGL_LIBRARIES})

#gorilla-audio
include_directories(external/gorilla-audio/include)
link_directories(external/gorilla-audio/lib)
link_libraries(gorilla openal32)

#engine
set(ENGINE_SRC
        external/glew/src/glew.c

        embedded/embedded.cpp

        src/application/window.cpp
        src/application/input.cpp
        src/application/application.cpp

        src/gfx/api/context.cpp
        src/gfx/api/vertexbuffer.cpp
        src/gfx/api/indexbuffer.cpp
        src/gfx/api/vertexarray.cpp
        src/gfx/api/texture.cpp
        src/gfx/api/texture2d.cpp
        src/gfx/api/shaderresource.cpp
        src/gfx/api/shaderuniform.cpp
        src/gfx/api/shader.cpp
        src/gfx/layers/layer2d.cpp
        src/gfx/camera/camera.hpp
        src/gfx/renderer.cpp
        src/gfx/renderer2d.cpp
        src/gfx/renderer2d.hpp
        src/gfx/renderable2d.cpp
        src/gfx/text.cpp

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

        src/resources/font.cpp
        src/resources/fontmanager.cpp
        src/resources/texturemanager.cpp
        src/resources/shaderfactory.cpp
        src/resources/sound.cpp
        src/resources/soundmanager.cpp

        src/utils/log.cpp
        src/utils/timer.cpp
        src/utils/loadimage.cpp
        src/utils/string.cpp

        src/config.cpp)


add_library(xe SHARED ${ENGINE_SRC})