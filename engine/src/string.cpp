//
// Created by FLXR on 1/31/2019.
//

#include <cstring>
#include <libgen.h>
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
		string temp = str;
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

		char32_t temp[delimiters.size()];
		delimiters.to_wide_literal(temp);
		size_t end = str.find_first_of(temp);

		std::vector<string> result;

		while (end <= string::npos) {
			string token = str.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == string::npos) break;

			start = end + 1;

			char32_t temp[delimiters.size()];
			delimiters.to_wide_literal(temp);
			end = str.find_first_of(temp, start);
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
		int32 size = static_cast<int32>(strlen(str));

		std::wstring buff(size, '\0');

		MultiByteToWideChar(CP_UTF8, 0, str, -1, &buff[0], size);

		return buff;
	}
#endif

}
