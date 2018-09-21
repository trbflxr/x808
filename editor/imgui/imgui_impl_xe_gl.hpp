//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_IMGUI_IMPL_XE_GL_HPP
#define X808_IMGUI_IMPL_XE_GL_HPP


#include <imgui.h>
#include <imgui_dock.h>
#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/tvec2.hpp>
#include <xe/window/window.hpp>

namespace ImGui { namespace xe {

	void init(::xe::Window &window, bool loadDefaultFont = true);

	void processEvent(const ::xe::Event &event);

	void update(::xe::Window &window, float delta);
	void update(const ::xe::vec2 &mousePos, const ::xe::vec2i &windowSize, float delta);

	void render();

	void shutdown();

	void updateFontTexture();

}}

#endif //X808_IMGUI_IMPL_XE_GL_HPP
