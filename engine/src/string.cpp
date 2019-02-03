//
// Created by FLXR on 7/4/2018.
//

#include <cstring>
#include <libgen.h>
#include <codecvt>
#include <locale>
#include <xe/string.hpp>

#ifdef XE_PLATFORM_WINDOWS
	#include <windows.h>
#endif

namespace xe {

	const char *findToken(const char *str, const string &token) {
		const char *t = str;
		while ((t = strstr(t, token.data()))) {
			bool left = str == t || isspace(t[-1]);
			bool right = !t[token.size()] || isspace(t[token.size()]);

			if (left && right) return t;

			t += token.size();
		}
		return nullptr;
	}

	const char *findToken(const string &str, const string &token) {
		return findToken(str.data(), token);
	}

	string getBlock(const char *str, const char **outPosition) {
		const char *end = strstr(str, "}");
		if (!end) return string(str);

		if (outPosition) *outPosition = end;

		uint length = end - str + 1;
		return string(str, length);
	}

	string getBlock(const string &str, uint offset) {
		const char *s = str.data() + offset;
		return getBlock(s);
	}

	string getFileName(const string &str, bool includeExt) {
		std::string temp = str;
		char *s = basename(temp.data());

		size_t size = strlen(s);

		if (!includeExt) {
			int lastDot = -1;

			for (size_t i = 0; i < size; ++i) {
				if (s[i] == '.') {
					lastDot = static_cast<int>(i);
				}
			}

			if (lastDot != -1) {
				s[lastDot] = '\0';
			}
		}

		return s;
	}

	string getStatement(const char *str, const char **outPosition) {
		const char *end = strstr(str, ";");
		if (!end) return string(str);

		if (outPosition) *outPosition = end;

		uint length = end - str + 1;
		return string(str, length);
	}

	std::vector<string> tokenize(const string &str) {
		return splitString(str, " \t\n");
	}

	std::vector<string> splitString(const string &str, const string &delimiters) {
		size_t start = 0;
		size_t end = str.find_first_of(delimiters);

		std::vector<string> result;

		while (end <= string::npos) {
			string token = str.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == string::npos) break;

			start = end + 1;
			end = str.find_first_of(delimiters, start);
		}

		return result;
	}

	std::vector<string> splitString(const string &str, char delimiter) {
		return splitString(str, string(1, delimiter));
	}

	std::vector<string> getLines(const string &str) {
		return splitString(str, "\n");
	}

	bool startsWith(const string &str, const string &start) {
		return str.find(start) == 0;
	}

#ifdef XE_PLATFORM_WINDOWS

	std::wstring toWstring(const string &str) {
		return toWstring(str.c_str());
	}

	std::wstring toWstring(const char *str) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str);
	}

	string toString(const std::wstring &str) {
		int32 size = static_cast<int32>(str.size()) * 2;

		std::string buffer(size, '\0');

		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, &buffer[0], size, nullptr, nullptr);

		return buffer;
	}

#endif

	void wcharToUTF8(const uint &wchar, uint &utf8) {
		char *c = (char *) &utf8;

		if (wchar < 0x80) {
			utf8 = wchar;
		} else if (wchar < 0x800) {
			c[0] = static_cast<char>((wchar >> 6) | 0xC0);
			c[1] = static_cast<char>((wchar & 0x3F) | 0x80);
		} else if (wchar < 0x10000) {
			c[0] = static_cast<char>((wchar >> 12) | 0xE0);
			c[1] = static_cast<char>(((wchar >> 6) & 0x3F) | 0x80);
			c[2] = static_cast<char>((wchar & 0x3F) | 0x80);
		} else if (wchar < 0x110000) {
			c[0] = static_cast<char>((wchar >> 18) | 0xF0);
			c[1] = static_cast<char>(((wchar >> 12) & 0x3F) | 0x80);
			c[2] = static_cast<char>(((wchar >> 6) & 0x3F) | 0x80);
			c[3] = static_cast<char>((wchar & 0x3F) | 0x80);
		}
	}

}