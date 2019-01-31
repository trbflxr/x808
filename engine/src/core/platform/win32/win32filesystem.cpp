//
// Created by FLXR on 1/31/2019.
//

#include <windows.h>

#include <xe/core/filesystem.hpp>

namespace xe {

	void CALLBACK fileIOCompletionRoutine(DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED overlapped) { }

	static HANDLE openFileForReading(const wstring &path) {
		return CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
		                   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
	}

	static int64 getFileSizeInternal(HANDLE file) {
		LARGE_INTEGER size;
		GetFileSizeEx(file, &size);
		return size.QuadPart;
	}

	static bool readFileInternal(HANDLE file, void *buffer, int64 size) {
		OVERLAPPED ol = {0};
		return (bool) ReadFileEx(file, buffer, static_cast<DWORD>(size), &ol, fileIOCompletionRoutine);
	}


	bool FileSystem::exists(const wstring &file) {
		DWORD result = GetFileAttributesW(file.c_str());
		return !(result == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
	}

	int64 FileSystem::size(const wstring &file) {
		HANDLE handle = openFileForReading(file);
		if (handle == INVALID_HANDLE_VALUE) return -1;

		int64 result = getFileSizeInternal(handle);
		CloseHandle(handle);

		return result;
	}

	byte *FileSystem::read(const wstring &file) {
		HANDLE handle = openFileForReading(file);
		int64 size = getFileSizeInternal(handle);
		byte *buffer = new byte[size];

		bool result = readFileInternal(handle, buffer, size);
		CloseHandle(handle);

		if (!result) {
			delete[] buffer;
		}

		return result ? buffer : nullptr;
	}

	bool FileSystem::read(const wstring &file, void *buff, int64 size) {
		HANDLE handle = openFileForReading(file);
		if (handle == INVALID_HANDLE_VALUE) return false;

		if (size < 0) {
			size = getFileSizeInternal(handle);
		}

		bool result = readFileInternal(handle, buff, size);
		CloseHandle(handle);

		return result;
	}

	bool FileSystem::write(const wstring &file, void *buff) {
		HANDLE handle = CreateFileW(file.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW | OPEN_EXISTING,
		                            FILE_ATTRIBUTE_NORMAL, nullptr);
		if (handle == INVALID_HANDLE_VALUE) return false;

		int64 size = getFileSizeInternal(handle);
		DWORD written;
		int32 result = ::WriteFile(handle, buff, static_cast<DWORD>(size), &written, nullptr);
		CloseHandle(handle);

		return static_cast<bool>(result);
	}

}