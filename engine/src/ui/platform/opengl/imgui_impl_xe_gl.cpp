//
// Created by FLXR on 9/7/2018.
//


#include <GL/glew.h>
#include <xe/gfx/texture.hpp>
#include <xe/utils/logger.hpp>
#include <xe/ui/imgui/imgui_impl_xe.hpp>
#include <embedded/embedded.hpp>

static bool windowHasFocus = false;
static bool mousePressed[3] = {false, false, false};
static ::xe::Texture *fontTexture = nullptr;

static uint shaderHandle;
static int32 samlper0;
static int32 projectionLoc;

static uint vbo;
static uint ibo;

static const char *vs = R"(
	#version 330
	layout (location = 0) in vec2 pos;
	layout (location = 1) in vec2 uv;
	layout (location = 2) in vec4 color;
	out vec2 uv0;
	out vec4 color0;
	uniform mat4 projection;
	void main() {
		uv0 = uv;
		color0 = color;
		gl_Position = projection * vec4(pos, 0 ,1);
	}
)";

static const char *fs = R"(
	#version 330
	layout (location = 0) out vec4 color;
	in vec2 uv0;
	in vec4 color0;
	uniform sampler2D sampler0;
	void main() {
	    color = color0 * texture(sampler0, uv0);
	}
)";


static bool checkShader(uint handle, const char *desc);
static bool checkProgram(uint handle, const char *desc);


void renderDrawLists(ImDrawData *drawData);

namespace ImGui::xe {

  void init(::xe::Window &window, bool loadDefaultFont) {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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

    windowHasFocus = window.hasFocus();


    if (glewInit() != GLEW_OK) {
      printf("Could not initialize GLEW!");
    }


    //create shaders
    uint vsHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsHandle, 1, &vs, nullptr);
    glCompileShader(vsHandle);
    checkShader(vsHandle, "vertex shader");

    uint fsHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsHandle, 1, &fs, nullptr);
    glCompileShader(fsHandle);
    checkShader(fsHandle, "fragment shader");


    shaderHandle = glCreateProgram();
    glAttachShader(shaderHandle, vsHandle);
    glAttachShader(shaderHandle, fsHandle);
    glLinkProgram(shaderHandle);
    checkProgram(shaderHandle, "shader program");

    glDetachShader(shaderHandle, vsHandle);
    glDetachShader(shaderHandle, fsHandle);

    glDeleteShader(vsHandle);
    glDeleteShader(fsHandle);

    samlper0 = glGetUniformLocation(shaderHandle, "sampler0");
    projectionLoc = glGetUniformLocation(shaderHandle, "projection");

    //buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

  }

  void shutdown() {
    ImGui::GetIO().Fonts->TexID = nullptr;

    delete fontTexture;
    fontTexture = nullptr;

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

    glDeleteProgram(shaderHandle);

    ImGui::DestroyContext();
  }

  void processEvent(::xe::Event &event) {
    if (event.type == ::xe::Event::LostFocus) {
      windowHasFocus = false;
    } else if (event.type == ::xe::Event::GainedFocus) {
      windowHasFocus = true;
    }

    if (windowHasFocus) {
      ImGuiIO &io = ImGui::GetIO();

      switch (event.type) {
        case ::xe::Event::MouseButtonPressed: // fall-through
        case ::xe::Event::MouseButtonReleased: {
          const int32 button = event.mouseButton.button;
          if (event.type == ::xe::Event::MouseButtonPressed && button >= 0 && button < 3) {
            mousePressed[event.mouseButton.button] = true;
            event.handled = io.WantCaptureMouse;
          }
          break;
        }

        case ::xe::Event::MouseWheelMoved: {
          io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
          event.handled = io.WantCaptureMouse;
          break;
        }

        case ::xe::Event::KeyPressed: // fall-through
        case ::xe::Event::KeyReleased: {
          io.KeysDown[event.key.code] = (event.type == ::xe::Event::KeyPressed);
          io.KeyCtrl = event.key.control;
          io.KeyShift = event.key.shift;
          io.KeyAlt = event.key.alt;

          event.handled = io.WantCaptureKeyboard;
          break;
        }

        case ::xe::Event::TextEntered: {
          if (event.text.unicode > 0 && event.text.unicode < 0x10000) {
            io.AddInputCharactersUTF8((const char *) &event.text.unicode);
          }
          event.handled = io.WantCaptureKeyboard;
          break;
        }

        default: break;
      }
    }
  }

  void update(::xe::Window &window, float delta) {
    update(::xe::Mouse::getPosition(window), window.getSize(), delta);

    if (ImGui::GetIO().MouseDrawCursor) {
      window.setMouseCursorVisible(false);
    }
  }

  void update(const ::xe::vec2 &mousePos, const ::xe::vec2 &windowSize, float delta) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize.x = windowSize.x;
    io.DisplaySize.y = windowSize.y;
    io.DeltaTime = delta > 0.0f ? delta : 0.0f;

    if (windowHasFocus) {
      if (io.WantSetMousePos) {
        ::xe::Mouse::setPosition({io.MousePos.x, windowSize.y - io.MousePos.y});
      } else {
        io.MousePos.x = mousePos.x;
        io.MousePos.y = windowSize.y - mousePos.y;
      }
      for (uint i = 0; i < 3; i++) {
        io.MouseDown[i] = mousePressed[i] || ::xe::Mouse::isButtonPressed((::xe::Mouse::Button) i);
        mousePressed[i] = false;
      }
    }

    assert(io.Fonts->Fonts.Size > 0);
  }

  void newFrame() {
    ImGui::NewFrame();
  }

  void render() {
    ImGui::Render();
    renderDrawLists(ImGui::GetDrawData());
  }

  void updateFontTexture() {
    static ::xe::TextureParameters params(::xe::TextureTarget::Tex2D,
                                          ::xe::PixelInternalFormat::Rgba,
                                          ::xe::PixelFormat::Rgba,
                                          ::xe::PixelType::UnsignedByte);

    ImGuiIO &io = ImGui::GetIO();
    byte *pixels;
    int32 width, height;

    ImFontConfig cfg = ImFontConfig();
    cfg.FontDataOwnedByAtlas = false;
    cfg.MergeMode = false;
    cfg.SizePixels = 16.0f;
    io.Fonts->AddFontFromMemoryTTF(::xe::internal::DEFAULT_FONT_DATA,
                                   ::xe::internal::DEFAULT_FONT_DATA_SIZE,
                                   16.0f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);


    delete fontTexture;
    fontTexture = new ::xe::Texture("ImGuiFont", width, height, 1, params);
    fontTexture->setData2D(pixels);


    io.Fonts->TexID = reinterpret_cast<ImTextureID>(fontTexture->getHandle());
  }

}

void renderDrawLists(ImDrawData *drawData) {
  // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
  ImGuiIO &io = ImGui::GetIO();

  uint fbWidth = static_cast<uint>(drawData->DisplaySize.x * io.DisplayFramebufferScale.x);
  uint fbHeight = static_cast<uint>(drawData->DisplaySize.y * io.DisplayFramebufferScale.y);

  if (fbWidth <= 0 || fbHeight <= 0) return;

  drawData->ScaleClipRects(io.DisplayFramebufferScale);

  // Backup GL state
  uint lastActiveTexture;
  uint lastShader;
  uint lastTexture;
  uint lastSampler;
  uint lastArrayBuffer;
  uint lastVertexArray;
  uint lastPolygonMode[2];
  uint lastViewport[4];
  uint lastScissorBox[4];
  uint lastBlendSrcRGB;
  uint lastBlendDstRGB;
  uint lastBlendSrcAlpha;
  uint lastBlendDstAlpha;
  uint lastBlendEquationRGB;
  uint lastBlendEquationAlpha;

  glGetIntegerv(GL_ACTIVE_TEXTURE, (int32 *) &lastActiveTexture);
  glActiveTexture(GL_TEXTURE0);

  glGetIntegerv(GL_CURRENT_PROGRAM, (int32 *) &lastShader);
  glGetIntegerv(GL_TEXTURE_BINDING_2D, (int32 *) &lastTexture);

#ifdef GL_SAMPLER_BINDING
  glGetIntegerv(GL_SAMPLER_BINDING, (int32 *) &lastSampler);
#endif

  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (int32 *) &lastArrayBuffer);
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (int32 *) &lastVertexArray);

#ifdef GL_POLYGON_MODE
  glGetIntegerv(GL_POLYGON_MODE, (int32 *) lastPolygonMode);
#endif

  glGetIntegerv(GL_VIEWPORT, (int32 *) lastViewport);
  glGetIntegerv(GL_SCISSOR_BOX, (int32 *) lastScissorBox);
  glGetIntegerv(GL_BLEND_SRC_RGB, (int32 *) &lastBlendSrcRGB);
  glGetIntegerv(GL_BLEND_DST_RGB, (int32 *) &lastBlendDstRGB);
  glGetIntegerv(GL_BLEND_SRC_ALPHA, (int32 *) &lastBlendSrcAlpha);
  glGetIntegerv(GL_BLEND_DST_ALPHA, (int32 *) &lastBlendDstAlpha);
  glGetIntegerv(GL_BLEND_EQUATION_RGB, (int32 *) &lastBlendEquationRGB);
  glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (int32 *) &lastBlendEquationAlpha);

  bool last_enable_blend = glIsEnabled(GL_BLEND);
  bool last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
  bool last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
  bool last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

  // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_SCISSOR_TEST);
#ifdef GL_POLYGON_MODE
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

  glViewport(0, 0, fbWidth, fbHeight);

  const float L = drawData->DisplayPos.x;
  const float R = drawData->DisplayPos.x + drawData->DisplaySize.x;
  const float T = drawData->DisplayPos.y;
  const float B = drawData->DisplayPos.y + drawData->DisplaySize.y;
  const float ortho_projection[4][4] = {
      {2.0f / (R - L),    0.0f,              0.0f,  0.0f},
      {0.0f,              2.0f / (T - B),    0.0f,  0.0f},
      {0.0f,              0.0f,              -1.0f, 0.0f},
      {(R + L) / (L - R), (T + B) / (B - T), 0.0f,  1.0f},
  };

  glUseProgram(shaderHandle);
  glUniform1i(samlper0, 0);
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &ortho_projection[0][0]);

#ifdef GL_SAMPLER_BINDING
  glBindSampler(0, 0);
#endif

  uint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (void *) IM_OFFSETOF(ImDrawVert, pos));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (void *) IM_OFFSETOF(ImDrawVert, uv));
  glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (void *) IM_OFFSETOF(ImDrawVert, col));

  // Draw
  ImVec2 pos = drawData->DisplayPos;
  for (int32 n = 0; n < drawData->CmdListsCount; ++n) {
    const ImDrawList *cmdList = drawData->CmdLists[n];
    const ImDrawIdx *idxBufferOffset = nullptr;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cmdList->VtxBuffer.Size * sizeof(ImDrawVert),
                 cmdList->VtxBuffer.Data, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cmdList->IdxBuffer.Size * sizeof(ImDrawIdx),
                 cmdList->IdxBuffer.Data, GL_STREAM_DRAW);

    for (int32 i = 0; i < cmdList->CmdBuffer.Size; ++i) {
      const ImDrawCmd *cmd = &cmdList->CmdBuffer[i];
      if (cmd->UserCallback) {
        // User callback (registered via ImDrawList::AddCallback)
        cmd->UserCallback(cmdList, cmd);
      } else {
        const ImVec4 clipRect = ImVec4(cmd->ClipRect.x - pos.x, cmd->ClipRect.y - pos.y,
                                       cmd->ClipRect.z - pos.x, cmd->ClipRect.w - pos.y);

        if (clipRect.x < fbWidth && clipRect.y < fbHeight && clipRect.z >= 0.0f && clipRect.w >= 0.0f) {
          glScissor((int32) clipRect.x,
                    (int32) (fbHeight - clipRect.w),
                    (int32) (clipRect.z - clipRect.x),
                    (int32) (clipRect.w - clipRect.y));

          glBindTexture(GL_TEXTURE_2D, (uint) (intptr_t) cmd->TextureId);
          glDrawElements(GL_TRIANGLES, (GLsizei) cmd->ElemCount, GL_UNSIGNED_SHORT, idxBufferOffset);
        }
      }
      idxBufferOffset += cmd->ElemCount;
    }
  }
  glDeleteVertexArrays(1, &vao);

  // Restore modified GL state
  glUseProgram(lastShader);
  glBindTexture(GL_TEXTURE_2D, lastTexture);

#ifdef GL_SAMPLER_BINDING
  glBindSampler(0, lastSampler);
#endif

  glActiveTexture(lastActiveTexture);
  glBindVertexArray(lastVertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer);
  glBlendEquationSeparate(lastBlendEquationRGB, lastBlendEquationAlpha);
  glBlendFuncSeparate(lastBlendSrcRGB, lastBlendDstRGB, lastBlendSrcAlpha, lastBlendDstAlpha);

  last_enable_blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
  last_enable_cull_face ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
  last_enable_depth_test ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
  last_enable_scissor_test ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);

#ifdef GL_POLYGON_MODE
  glPolygonMode(GL_FRONT_AND_BACK, lastPolygonMode[0]);
#endif

  glViewport(lastViewport[0], lastViewport[1], (GLsizei) lastViewport[2], (GLsizei) lastViewport[3]);
  glScissor(lastScissorBox[0], lastScissorBox[1], (GLsizei) lastScissorBox[2], (GLsizei) lastScissorBox[3]);

}

static bool checkShader(uint handle, const char *desc) {
  int32 status;
  int32 logLength;

  glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
  glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);

  if (status == GL_FALSE) {
    fprintf(stderr, "ERROR: ImGui_Init: failed to compile %s!\n", desc);

    if (logLength > 0) {
      ImVector<char> buf;
      buf.resize((int) (logLength + 1));
      glGetShaderInfoLog(handle, logLength, nullptr, buf.begin());
      fprintf(stderr, "%s\n", buf.begin());
    }

    return false;
  }

  return true;
}

static bool checkProgram(uint handle, const char *desc) {
  int32 status;
  int32 logLength;

  glGetProgramiv(handle, GL_LINK_STATUS, &status);
  glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

  if (status == GL_FALSE) {
    fprintf(stderr, "ERROR: ImGui_Init: failed to link %s!\n", desc);

    if (logLength > 0) {
      ImVector<char> buf;
      buf.resize((int) (logLength + 1));
      glGetProgramInfoLog(handle, logLength, nullptr, buf.begin());
      fprintf(stderr, "%s\n", buf.begin());
    }

    return false;
  }

  return true;
}