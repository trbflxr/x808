//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_IMGUI_IMPL_XE_GL_HPP
#define X808_IMGUI_IMPL_XE_GL_HPP


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>
#include <xe/window/window.hpp>

namespace ImGui { namespace xe {

	void init(::xe::Window &window, bool loadDefaultFont = true);

	void processEvent(const ::xe::Event &event);

	void update(::xe::Window &window, float delta);
	void update(const ::xe::vec2 &mousePos, const ::xe::vec2 &windowSize, float delta);

	void render();

	void shutdown();

	void updateFontTexture();

}}

#endif //X808_IMGUI_IMPL_XE_GL_HPP
