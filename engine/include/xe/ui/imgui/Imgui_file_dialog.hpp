//
// Created by FLXR on 2/28/2019.
//

#ifndef X808_IMGUI_FILE_DIALOG_HPP
#define X808_IMGUI_FILE_DIALOG_HPP


#include <vector>
#include <functional>
#include <xe/string.hpp>
#include <xe/xeint.hpp>
#include <xe/common.hpp>

#define MAX_FILE_DIALOG_NAME_BUFFER 1024

namespace xe {

  enum class EntryType {
    Invalid,
    Directory,
    File,
    Link
  };

  struct FileInfo {
    EntryType type;
    string name;
    string path;
  };

  class XE_API ImGuiFileDialog {
  public:
    static void reset();

    static bool open(const char *title);
    static bool save(const char *title);

    inline static const std::vector<FileInfo> &getFiles() { return get().selectedFiles; }
    inline static string getSavePath() { return get().savePath; }

  private:
    explicit ImGuiFileDialog();

    static ImGuiFileDialog &get();

    void resetInternal();

    bool openInternal(const char *title);
    bool saveInternal(const char *title);

    void fileDialogBaseBegin(const char *title, const std::function<void(void *, const FileInfo &)> &logic);
    void fileDialogBaseEnd();

    void composeNewPath(std::vector<string>::iterator it);

    void scanDir(string path);

  private:
    char fileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
    std::vector<FileInfo> selectedFiles;

    std::string currentPath;
    std::vector<string> currentPathDecomposition;

    std::vector<FileInfo> files;

    string savePath;
  };

}

#endif //X808_IMGUI_FILE_DIALOG_HPP
