//
// Created by FLXR on 11/14/2018.
//

#ifndef X808_SHELL_HPP
#define X808_SHELL_HPP


#include <vector>
#include <deque>
#include <unordered_map>
#include <functional>
#include <xe/common.hpp>
#include <xe/systems/system.hpp>

struct ImGuiInputTextCallbackData;

namespace xe {

  enum class ShellItemType {
    Command, Info, Warn, Error, Fatal
  };

  struct ShellItem {
    string str;
    ShellItemType type;
  };

  class XE_API Shell : public System {
  public:
    explicit Shell();
    ~Shell() override;

    void render() override;

    void update(float delta) override;
    void input(Event &event) override;

    void executeCommand(const string &command);

    bool addCommand(const string &command, const std::function<string(const std::vector<string> &, bool)> &callback);

    void printString(const char *str, ShellItemType type, bool newLine = true);

  private:
    void createDefaultCommands();

    void clear();

    void addLog(ShellItemType type, const char *fmt, ...) XE_FMT_ARGS(3);

    static int32 textEditCallbackStub(ImGuiInputTextCallbackData *data);
    int32 textEditCallback(ImGuiInputTextCallbackData *data);

  private:
    bool shouldClose;

    bool scrollToBottom;
    bool focusInput;

    static constexpr byte HISTORY_SIZE = 10;

    char inputBuffer[256];
    std::vector<ShellItem> items;
    std::deque<string> history;
    int32 historyPos;

    std::unordered_map<string, std::function<string(const std::vector<string> &, bool)>> commands;
  };

}


#endif //X808_SHELL_HPP
