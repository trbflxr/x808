//
// Created by FLXR on 7/4/2018.
//

#include <cstring>
#include <libgen.h>
#include <codecvt>
#include <locale>
#include <xe/utils/string.hpp>

namespace xe { namespace utils {

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

	wstring toWstring(const string &str) {
		return toWstring(str.c_str());
	}

	wstring toWstring(const char *str) {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str);
	}

}}