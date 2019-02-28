//
// Created by FLXR on 2/28/2019.
//

#include <xe/ui/imgui/Imgui_file_dialog.hpp>
#include <xe/ui/imgui/imgui.h>
#include <xe/utils/logger.hpp>
#include <xe/core/filesystem.hpp>
#include <algorithm>
#include <dirent.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <xe/ui/imgui/imgui_internal.h>

namespace xe {

	static int32 sort(const dirent **a, const dirent **b) {
		return strcoll(((dirent *) a)->d_name, ((dirent *) b)->d_name);
	}

	static bool comparator(const FileInfo &a, const FileInfo &b) {
		if (a.type != b.type) {
			return a.type < b.type;
		}
		if (a.name == "..") {
			return true;
		}
		return a.name < b.name;
	}

	ImGuiFileDialog::ImGuiFileDialog() {

	}

	ImGuiFileDialog &ImGuiFileDialog::get() {
		static ImGuiFileDialog fd;
		return fd;
	}

	void ImGuiFileDialog::reset() {
		get().resetInternal();
	}

	void ImGuiFileDialog::resetInternal() {
		fileNameBuffer[0] = '\0';
		selectedFiles.clear();
		files.clear();
		currentPathDecomposition.clear();
		currentPath = "";
		savePath = "";
	}

	bool ImGuiFileDialog::open(const char *title) {
		return get().openInternal(title);
	}

	bool ImGuiFileDialog::save(const char *title) {
		return get().saveInternal(title);
	}

	bool ImGuiFileDialog::saveInternal(const char *title) {
		bool r = false;

		auto logic = [&](void *fd, const FileInfo &info) {
			ImGuiFileDialog *d = (ImGuiFileDialog *) fd;
			if (d->selectedFiles.empty()) {
				d->selectedFiles.push_back(info);
			} else {
				d->selectedFiles.pop_back();
				d->selectedFiles.push_back(info);
			}
		};

		fileDialogBaseBegin(title, logic);
		if (ImGui::Button("Save")) {
			if (fileNameBuffer[0] != '\0' && !currentPath.empty()) {
				savePath = currentPath + "/" + fileNameBuffer;
			} else {
				savePath = "";
			}

			r = true;
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			r = true;
			selectedFiles.clear();
		}
		fileDialogBaseEnd();

		return r;
	}

	bool ImGuiFileDialog::openInternal(const char *title) {
		bool r = false;

		auto logic = [&](void *fd, const FileInfo &info) {
			ImGuiFileDialog *d = (ImGuiFileDialog *) fd;

			if (ImGui::GetIO().KeyCtrl) {
				int32 found = -1;
				for (size_t i = 0; i < d->selectedFiles.size(); ++i) {
					if (d->selectedFiles[i].name == info.name) {
						found = static_cast<int32>(i);
						break;
					}
				}

				if (found != -1) {
					d->selectedFiles.erase(d->selectedFiles.begin() + found);
				} else {
					d->selectedFiles.push_back(info);
				}

			} else {
				d->selectedFiles.clear();
				d->selectedFiles.push_back(info);
			}
		};

		fileDialogBaseBegin(title, logic);
		if (ImGui::Button("Open")) {
			r = true;
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			r = true;
			selectedFiles.clear();
		}
		fileDialogBaseEnd();

		return r;
	}

	void ImGuiFileDialog::fileDialogBaseBegin(const char *title,
	                                          const std::function<void(void *, const FileInfo &)> &logic) {

		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse |
		                                ImGuiWindowFlags_NoDocking;

		ImGui::Begin(title, nullptr, flags);

		bool pathClicked = false;
		//drives
		for (const auto &d : FileSystem::getLogicalDrives()) {
			ImGui::SameLine();
			if (ImGui::Button(d.c_str())) {
				pathClicked = true;
				currentPath = d;
				currentPathDecomposition.clear();
			}
		}

		//working dir
		ImGui::SameLine();
		if (ImGui::Button("Working dir")) {
			pathClicked = true;
			currentPath = FileSystem::getWorkingDirectory();
			currentPathDecomposition.clear();
		}

		ImGui::Separator();

		//current path
		ImGui::NewLine();
		for (auto it = currentPathDecomposition.begin(); it != currentPathDecomposition.end(); ++it) {
			ImGui::SameLine();
			if (ImGui::Button((*it).c_str())) {
				composeNewPath(it);
				pathClicked = true;
				break;
			}
		}

		ImGui::Separator();

		ImVec2 size = ImGui::GetContentRegionMax() - ImVec2(0.0f, 152.0f);
		ImGui::BeginChild("##FileDialog_FileList", size);

		for (auto &&info : files) {
			string s;
			switch (info.type) {
				case EntryType::Directory: {
					s = "[dir] " + info.name;
					break;
				}
				case EntryType::File: {
					s = "[file] " + info.name;
					break;
				}
				case EntryType::Link: {
					s = "[link] " + info.name;
					break;
				}
				default:
				case EntryType::Invalid: {
					s = "[---] " + info.name;
					break;
				}
			}

			bool selected = false;
			for (const auto &f : selectedFiles) {
				if (f.name == info.name) {
					selected = true;
					break;
				}
			}

			if (ImGui::Selectable(s.c_str(), selected)) {
				if (info.type == EntryType::Directory) {
					if (info.name == "..") {
						if (currentPathDecomposition.size() > 1) {
							composeNewPath(currentPathDecomposition.end() - 2);
						} else if (currentPathDecomposition.size() == 1) {
							composeNewPath(currentPathDecomposition.end() - 1);
						}
					} else {
						currentPath += "/" + info.name;
					}
					pathClicked = true;
					selectedFiles.clear();
				} else if (info.type == EntryType::File) {
					fileNameBuffer[0] = '\0';
					strcpy(fileNameBuffer, info.name.c_str());

					logic(this, info);
				}
				break;
			}
		}

		if (pathClicked) {
			scanDir(currentPath);
			currentPathDecomposition = splitString(currentPath, "/");
		}

		ImGui::EndChild();

		ImGui::Separator();

		ImGui::Text("File name : ");
		ImGui::SameLine();

		const float width = ImGui::GetContentRegionAvailWidth();
		ImGui::PushItemWidth(width);
		ImGui::InputText("##FileName", fileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER);
		ImGui::PopItemWidth();

		ImGui::Separator();
	}

	void ImGuiFileDialog::fileDialogBaseEnd() {
		ImGui::End();
	}

	void ImGuiFileDialog::composeNewPath(std::vector<string>::iterator it) {
		currentPath.clear();

		while (it != currentPathDecomposition.begin()) {
			if (!currentPath.empty()) {
				currentPath = *it + "/" + currentPath;
			} else {
				currentPath = *it;
			}
			--it;
		}

		if (!currentPath.empty()) {
			currentPath = *it + "/" + currentPath;
		} else {
			currentPath = *it + "/";
		}
	}

	void ImGuiFileDialog::scanDir(string path) {
		files.clear();

		if (currentPathDecomposition.empty()) {
			DIR *dir = opendir(path.c_str());
			if (dir) {
				currentPath = toString(dir->wdirp->patt);
				closedir(dir);

				replaceAll(currentPath, "\\", "/");

				size_t pos = currentPath.find_last_of("/*");
				currentPath.erase(pos - 1);

				currentPathDecomposition = splitString(currentPath, "/");
			} else {
				return;
			}
		}

		dirent **entries = nullptr;
		int32 n = scandir(path.c_str(), &entries, nullptr, sort);

		if (n <= 0) return;

		for (int32 i = 0; i < n; ++i) {
			dirent *e = entries[i];

			if (strcmp(e->d_name, ".") == 0) continue;

			FileInfo info;
			info.name = e->d_name;
			info.path = currentPath + "/" + e->d_name;

			switch (e->d_type) {
				case DT_REG: info.type = EntryType::File;
					break;
				case DT_DIR: info.type = EntryType::Directory;
					break;
				case DT_LNK: info.type = EntryType::Link;
					break;
				default: info.type = EntryType::Invalid;
			}

			files.push_back(info);
		}

		for (int32 i = 0; i < n; ++i) {
			delete entries[i];
		}
		delete entries;

		std::sort(files.begin(), files.end(), comparator);
	}

}