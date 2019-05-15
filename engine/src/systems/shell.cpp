//
// Created by FLXR on 11/14/2018.
//

#include <sstream>
#include <xe/systems/shell.hpp>
#include <xe/gfx/context.hpp>
#include <xe/gfx/renderer.hpp>
#include <xe/utils/logger.hpp>
#include <xe/ui/imgui/imgui_impl_xe.hpp>

namespace xe {

  Shell::Shell() :
      shouldClose(false),
      scrollToBottom(false),
      focusInput(true),
      historyPos(-1) {
    createDefaultCommands();

    memset(inputBuffer, 0, sizeof(inputBuffer));
  }

  Shell::~Shell() {
    clear();
  }

  void Shell::render() {
    if (!active) return;

    static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse |
                                          ImGuiWindowFlags_NoResize |
                                          ImGuiWindowFlags_NoMove |
                                          ImGuiWindowFlags_NoBringToFrontOnFocus |
                                          ImGuiWindowFlags_NoNavFocus |
                                          ImGuiWindowFlags_NoDocking;

    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {5.0f, 8.0f});

    ImGui::Begin("Shell", nullptr, windowFlags);
    ImGui::PopStyleVar(3);


    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    static ImGuiTextFilter filter;
    filter.Draw("Filter: type '-' to exclude", 180);
    ImGui::PopStyleVar();
    ImGui::Separator();

    const float height = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", {0.0f, -height}, false, ImGuiWindowFlags_HorizontalScrollbar);


    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {4.0f, 1.0f});

    ImVec4 defaultTextColor = ImGui::GetStyleColorVec4(ImGuiCol_Text);
    for (const auto &s : items) {
      const char *item = s.str.c_str();
      if (!filter.PassFilter(item)) continue;

      ImVec4 textColor = defaultTextColor;
      switch (s.type) {
        case ShellItemType::Command: textColor = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
          break;
        case ShellItemType::Warn: textColor = ImColor(1.0f, 1.0f, 0.1f, 1.0f);
          break;
        case ShellItemType::Error: textColor = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
          break;
        case ShellItemType::Fatal: textColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
          break;
        default: break;
      }

      ImGui::PushStyleColor(ImGuiCol_Text, textColor);
      ImGui::TextUnformatted(item);
      ImGui::PopStyleColor();
    }

    if (scrollToBottom) {
      ImGui::SetScrollHereY(1.0f);
    }
    scrollToBottom = false;

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();

    bool reclaimFocus = false;
    const bool inputText = ImGui::InputText("Input", inputBuffer, IM_ARRAYSIZE(inputBuffer),
                                            ImGuiInputTextFlags_EnterReturnsTrue |
                                            ImGuiInputTextFlags_CallbackCompletion |
                                            ImGuiInputTextFlags_CallbackHistory,
                                            &textEditCallbackStub, this);
    if (inputText) {
      string cmd(inputBuffer);

      if (cmd[0]) {
        executeCommand(cmd);
      }

      strcpy(inputBuffer, "");

      reclaimFocus = true;
    }


    ImGui::SetItemDefaultFocus();
    if (reclaimFocus || focusInput) {
      ImGui::SetKeyboardFocusHere(-1);
      focusInput = false;
    }

    ImGui::End();
  }

  void Shell::update(float delta) {
    if (shouldClose) {
      shouldClose = false;
    }
  }

  void Shell::input(Event &event) {
    if (shouldClose) {
      event.handled = true;
      return;
    }

    if (active) {
      event.handled = true;
    }

    if (event.type == Event::KeyPressed) {
      if (event.key.code == Keyboard::Tilde && event.key.control) {
        if (active) {
          shouldClose = true;
          active = false;
        } else {
          active = true;
          focusInput = true;
        }
        event.handled = true;
      }
      if (event.key.code == Keyboard::Escape && active) {
        shouldClose = true;
        active = false;
        event.handled = true;
      }
    }
  }

  bool Shell::addCommand(const string &command,
                         const std::function<string(const std::vector<string> &, bool)> &callback) {

    auto &&it = commands.find(command);
    if (it == commands.end()) {
      commands[command] = callback;
      return true;
    } else {
      XE_CORE_ERROR("[Shell]: Command '", command, "' already exists");
      return false;
    }
  }

  void Shell::executeCommand(const string &command) {
    addLog(ShellItemType::Command, "# %s\n", command.c_str());

    historyPos = -1;
    if (history.size() >= HISTORY_SIZE) {
      history.pop_front();
    }

    history.push_back(command);

    std::vector<string> tokens = tokenize(command);

    auto &&it = commands.find(tokens[0]);
    if (it != commands.end()) {
      bool hint = false;
      if (tokens.size() > 1) {
        hint = tokens[1] == "-h";
      }

      tokens.erase(tokens.begin());
      string res = it->second(tokens, hint);

      if (!res.empty()) {
        ShellItemType type = ShellItemType::Info;

        if (startsWith(res, "[W]")) {
          res.erase(res.begin(), res.begin() + 3);
          type = ShellItemType::Warn;
        } else if (startsWith(res, "[E]")) {
          res.erase(res.begin(), res.begin() + 3);
          type = ShellItemType::Error;
        } else if (startsWith(res, "[F]")) {
          res.erase(res.begin(), res.begin() + 3);
          type = ShellItemType::Fatal;
        }

        addLog(type, "  %s\n", res.c_str());
      }

    } else {
      addLog(ShellItemType::Error, "Unknown command: '%s'\n", command.c_str());
    }

  }

  void Shell::clear() {
    items.clear();
    scrollToBottom = true;
  }

  void Shell::addLog(ShellItemType type, const char *fmt, ...) {
    char buff[1024];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buff, IM_ARRAYSIZE(buff), fmt, args);
    buff[IM_ARRAYSIZE(buff) - 1] = 0;
    va_end(args);

    items.push_back({strdup(buff), type});
    scrollToBottom = true;
  }

  int32 Shell::textEditCallbackStub(ImGuiInputTextCallbackData *data) {
    Shell *shell = reinterpret_cast<Shell *>(data->UserData);
    return shell->textEditCallback(data);
  }

  int32 Shell::textEditCallback(ImGuiInputTextCallbackData *data) {
    switch (data->EventFlag) {
      case ImGuiInputTextFlags_CallbackCompletion: {

        const char *wordEnd = data->Buf + data->CursorPos;
        const char *wordStart = wordEnd;

        while (wordStart > data->Buf) {
          const char c = wordStart[-1];
          if (c == ' ' || c == '\t' || c == ',' || c == ';') break;
          wordStart--;
        }

        std::vector<string> candidates;
        for (const auto &command : commands) {
          if (startsWith(command.first, wordStart)) {
            candidates.push_back(command.first);
          }
        }

        if (candidates.empty()) {
          addLog(ShellItemType::Info, "No match for \"%.*s\"\n", (int32) (wordEnd - wordStart), wordStart);
        } else if (candidates.size() == 1) {
          data->DeleteChars((int32) (wordStart - data->Buf), (int32) (wordEnd - wordStart));
          data->InsertChars(data->CursorPos, candidates[0].c_str());
        } else {
          //du = dummy1 && dummy2
          int32 matchLen = (int32) (wordEnd - wordStart);
          for (;;) {
            int32 c = 0;
            bool allCandidatesMatches = true;
            for (size_t i = 0; i < candidates.size() && allCandidatesMatches; ++i) {
              if (i == 0) {
                c = toupper(candidates[i][matchLen]);
              } else if (c == 0 || c != toupper(candidates[i][matchLen])) {
                allCandidatesMatches = false;
              }
            }

            if (!allCandidatesMatches) break;
            matchLen++;
          }

          if (matchLen > 0) {
            data->DeleteChars((int32) (wordStart - data->Buf), (int32) (wordEnd - wordStart));
            data->InsertChars(data->CursorPos, candidates[0].c_str(), candidates[0].c_str() + matchLen);
          }

          addLog(ShellItemType::Info, "Possible matches:\n");
          for (const auto &c : candidates) {
            addLog(ShellItemType::Info, "- %s\n", c.c_str());
          }
        }
        break;
      }
      case ImGuiInputTextFlags_CallbackHistory: {
        const int32 prevHistoryPos = historyPos;
        if (data->EventKey == ImGuiKey_UpArrow) {
          historyPos == -1 ? historyPos = (int32) history.size() - 1 : --historyPos;

        } else if (data->EventKey == ImGuiKey_DownArrow) {
          if (historyPos != -1) {
            if (++historyPos >= (int32) history.size()) {
              historyPos = -1;
            }
          }
        }

        if (prevHistoryPos != historyPos) {
          const char *historyStr = (historyPos >= 0) ? history[historyPos].c_str() : "";
          data->DeleteChars(0, data->BufTextLen);
          data->InsertChars(0, historyStr);
        }
      }
      default: break;
    }
    return 0;
  }

  void Shell::createDefaultCommands() {
    commands["help"] = [&](const std::vector<string> &args, bool hint) -> string {
      if (hint) return "Help";

      std::stringstream ss;

      ss << "Commands: \n";
      for (const auto &c : commands) {
        ss << "  - " << c.first << "\n";
      }

      return ss.str();
    };

    commands["info"] = [&](const std::vector<string> &args, bool hint) -> string {
      if (hint) return "Displays info.";

      const GAPIInfo info = Context::getInfo();

      std::stringstream ss;

      ss << "Context: \n";
      ss << "  - Vendor: " << info.vendor << "\n";
      ss << "  - Version: " << info.version << "\n";
      ss << "  - Renderer: " << info.renderer << "\n";
      ss << "  - Shading language: " << info.shadingLevel << "\n";
      ss << "  - Max texture size: " << info.maxTexSize << "\n";
      ss << "  - Max texture units: " << info.maxTexUnits << "\n";
      ss << "  - Max image units: " << info.maxTexImgUnits;

      return ss.str();
    };

    commands["config"] = [&](const std::vector<string> &args, bool hint) -> string {
      if (hint) return "Displays engine config.";

      std::stringstream ss;

      ss << "Config: \n";
      ss << "  - Width: " << Config::get().width << "\n";
      ss << "  - Height: " << Config::get().height << "\n";
      ss << "  - Fullscreen: " << Config::get().fullScreen << "\n";
      ss << "  - Vsync: " << Config::get().vSync << "\n";
      ss << "  - Target FPS: " << Config::get().maxFps << "\n";
      ss << "  - Target TPS: " << Config::get().tickRate << "\n";
      ss << "  - Use SRGB: " << Config::get().srgb << "\n";
      ss << "  - Render API: " << renderApiToString(Config::get().renderApi) << "\n";
      ss << "  - Render API version: " << Config::get().apiVersion << "\n";

      return ss.str();
    };

    commands["clear"] = [&](const std::vector<string> &args, bool hint) -> string {
      if (hint) return "Clears console.";
      clear();
      return "";
    };

    commands["args"] = [&](const std::vector<string> &args, bool hint) -> string {
      if (hint) return "Prints args.";

      std::stringstream ss;

      if (args.empty()) {
        ss << "No arguments given.";
        return ss.str();
      }

      for (size_t i = 0; i < args.size() - 1; ++i) {
        ss << "- " << args[i] << "\n  ";
      }
      ss << "- " << args[args.size() - 1];

      return ss.str();
    };
  }

}
