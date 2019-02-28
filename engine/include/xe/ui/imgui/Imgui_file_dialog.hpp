//
// Created by FLXR on 2/28/2019.
//

#ifndef X808_IMGUI_FILE_DIALOG_HPP
#define X808_IMGUI_FILE_DIALOG_HPP


#include <vector>
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

		inline static const std::vector<FileInfo> &getFiles() { return get().selectedFiles; }

	private:
		explicit ImGuiFileDialog();

		static ImGuiFileDialog &get();

		void resetInternal();

		bool openInternal(const char *title);

		void composeNewPath(std::vector<string>::iterator it);

		void scanDir(string path);

	private:
		char fileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
		std::vector<FileInfo> selectedFiles;

		std::string currentPath;
		std::vector<string> currentPathDecomposition;

		std::vector<FileInfo> files;
	};

}

#endif //X808_IMGUI_FILE_DIALOG_HPP
