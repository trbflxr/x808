//
// Created by FLXR on 9/7/2018.
//


#include <GL/glew.h>
#include <xe/gfx/texture.hpp>
#include <xe/utils/log.hpp>
#include "imgui.h"
#include "imgui_impl_xe_gl.hpp"


static bool s_windowHasFocus = false;
static bool s_mousePressed[3] = {false, false, false};
static ::xe::Texture *s_fontTexture = nullptr;

static ::xe::TextureParameters s_params(::xe::TextureTarget::Tex2D,
                                        ::xe::TextureWrap::Clamp,
                                        0, 0);

void renderDrawLists(ImDrawData *drawData);

namespace ImGui { namespace xe {

	void init(::xe::Window &window, bool loadDefaultFont) {
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// init keyboard mapping
		io.KeyMap[ImGuiKey_Tab] = ::xe::Keyboard::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = ::xe::Keyboard::Left;
		io.KeyMap[ImGuiKey_RightArrow] = ::xe::Keyboard::Right;
		io.KeyMap[ImGuiKey_UpArrow] = ::xe::Keyboard::Up;
		io.KeyMap[ImGuiKey_DownArrow] = ::xe::Keyboard::Down;
		io.KeyMap[ImGuiKey_PageUp] = ::xe::Keyboard::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = ::xe::Keyboard::PageDown;
		io.KeyMap[ImGuiKey_Home] = ::xe::Keyboard::Home;
		io.KeyMap[ImGuiKey_End] = ::xe::Keyboard::End;
		io.KeyMap[ImGuiKey_Insert] = ::xe::Keyboard::Insert;
		io.KeyMap[ImGuiKey_Delete] = ::xe::Keyboard::Delete;
		io.KeyMap[ImGuiKey_Backspace] = ::xe::Keyboard::BackSpace;
		io.KeyMap[ImGuiKey_Space] = ::xe::Keyboard::Space;
		io.KeyMap[ImGuiKey_Enter] = ::xe::Keyboard::Return;
		io.KeyMap[ImGuiKey_Escape] = ::xe::Keyboard::Escape;
		io.KeyMap[ImGuiKey_A] = ::xe::Keyboard::A;
		io.KeyMap[ImGuiKey_C] = ::xe::Keyboard::C;
		io.KeyMap[ImGuiKey_V] = ::xe::Keyboard::V;
		io.KeyMap[ImGuiKey_X] = ::xe::Keyboard::X;
		io.KeyMap[ImGuiKey_Y] = ::xe::Keyboard::Y;
		io.KeyMap[ImGuiKey_Z] = ::xe::Keyboard::Z;


		// init rendering
		io.DisplaySize.x = window.getSize().x;
		io.DisplaySize.y = window.getSize().y;

		if (loadDefaultFont) {
			updateFontTexture();
		}

		s_windowHasFocus = window.hasFocus();
	}

	void processEvent(const ::xe::Event &event) {
		if (s_windowHasFocus) {
			ImGuiIO &io = ImGui::GetIO();

			switch (event.type) {
				case ::xe::Event::MouseButtonPressed: // fall-through
				case ::xe::Event::MouseButtonReleased: {
					int32 button = event.mouseButton.button;
					if (event.type == ::xe::Event::MouseButtonPressed &&
					    button >= 0 && button < 3) {
						s_mousePressed[event.mouseButton.button] = true;
					}
				}
					break;

				case ::xe::Event::MouseWheelMoved: io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
					break;
				case ::xe::Event::KeyPressed: // fall-through
				case ::xe::Event::KeyReleased: io.KeysDown[event.key.code] = (event.type == ::xe::Event::KeyPressed);
					io.KeyCtrl = event.key.control;
					io.KeyShift = event.key.shift;
					io.KeyAlt = event.key.alt;
					break;

				case ::xe::Event::TextEntered:
					if (event.text.unicode > 0 && event.text.unicode < 0x10000) {
						io.AddInputCharacter(static_cast<ImWchar>(event.text.unicode));
					}
					break;

				default: break;
			}
		}

		switch (event.type) {
			case ::xe::Event::LostFocus: s_windowHasFocus = false;
				break;
			case ::xe::Event::GainedFocus: s_windowHasFocus = true;
				break;
			default: break;
		}
	}

	void update(::xe::Window &window, float delta) {
		update(::xe::Mouse::getPosition(window), window.getSize(), delta);

		if (ImGui::GetIO().MouseDrawCursor) {
			window.setMouseCursorVisible(false);
		}
	}

	void update(const ::xe::vec2i &mousePos, const ::xe::vec2i &windowSize, float delta) {
		ImGuiIO &io = ImGui::GetIO();
		io.DisplaySize.x = windowSize.x;
		io.DisplaySize.y = windowSize.y;
		io.DeltaTime = delta;

		if (s_windowHasFocus) {
			if (io.WantSetMousePos) {
				::xe::vec2i pos((int32) io.MousePos.x, (int32) io.MousePos.y);
				::xe::Mouse::setPosition(pos);
			} else {
				io.MousePos.x = mousePos.x;
				io.MousePos.y = mousePos.y;
			}
			for (uint i = 0; i < 3; i++) {
				io.MouseDown[i] = s_mousePressed[i] || ::xe::Mouse::isButtonPressed((::xe::Mouse::Button) i);
				s_mousePressed[i] = false;
			}
		}

		assert(io.Fonts->Fonts.Size > 0);

		ImGui::NewFrame();
	}

	void render() {
		ImGui::Render();
		renderDrawLists(ImGui::GetDrawData());
	}

	void shutdown() {
		ImGui::GetIO().Fonts->TexID = nullptr;

		delete s_fontTexture;
		s_fontTexture = nullptr;

		ImGui::DestroyContext();
	}

	void updateFontTexture() {
		ImGuiIO &io = ImGui::GetIO();
		byte *pixels;
		int32 width, height;

		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

		delete s_fontTexture;
		s_fontTexture = new ::xe::Texture("ImGuiFont", width, height, 0, s_params);
		s_fontTexture->setData2D(pixels);


		io.Fonts->TexID = reinterpret_cast<ImTextureID>(s_fontTexture->getHandle());
	}

}}

void renderDrawLists(ImDrawData *drawData) {
	ImGui::GetDrawData();
	if (drawData->CmdListsCount == 0) {
		return;
	}

	ImGuiIO &io = ImGui::GetIO();
	XE_ASSERT(io.Fonts->TexID != nullptr);

	// scale stuff (needed for proper handling of window resize)
	int32 fb_width = static_cast<int32>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int32 fb_height = static_cast<int32>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0) { return; }
	drawData->ScaleClipRects(io.DisplayFramebufferScale);

	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glViewport(0, 0, fb_width, fb_height);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (uint n = 0; n < drawData->CmdListsCount; ++n) {
		const ImDrawList *cmd_list = drawData->CmdLists[n];
		const byte *vtx_buffer = (const byte *) &cmd_list->VtxBuffer.front();
		const ImDrawIdx *idx_buffer = &cmd_list->IdxBuffer.front();

		glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void *) (vtx_buffer + offsetof(ImDrawVert, pos)));
		glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void *) (vtx_buffer + offsetof(ImDrawVert, uv)));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void *) (vtx_buffer + offsetof(ImDrawVert, col)));

		for (int32 cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); ++cmd_i) {
			const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback) {
				pcmd->UserCallback(cmd_list, pcmd);
			} else {
				uint texId = (uint) *((uint *) &pcmd->TextureId);
				glBindTexture(GL_TEXTURE_2D, texId);
				glScissor((int32) pcmd->ClipRect.x, (int32) (fb_height - pcmd->ClipRect.w),
				          (int32) (pcmd->ClipRect.z - pcmd->ClipRect.x), (int32) (pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
			}
			idx_buffer += pcmd->ElemCount;
		}
	}

	glPopAttrib();
}