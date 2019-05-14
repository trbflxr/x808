//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_IMGUI_IMPL_XE_GL_HPP
#define X808_IMGUI_IMPL_XE_GL_HPP


#include <xe/ui/imgui/imgui.h>
#include <xe/ui/imgui/imgui_internal.h>
#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>
#include <xe/window/window.hpp>

namespace ImGui::xe {

	XE_API void init(::xe::Window &window, bool loadDefaultFont = true);

	XE_API void processEvent(const ::xe::Event &event);

	XE_API void update(::xe::Window &window, float delta);
	XE_API void update(const ::xe::vec2 &mousePos, const ::xe::vec2 &windowSize, float delta);

	XE_API void newFrame();

	XE_API void render();

	XE_API void shutdown();

	XE_API void updateFontTexture();

}

#endif //X808_IMGUI_IMPL_XE_GL_HPP
