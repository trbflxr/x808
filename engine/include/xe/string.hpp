//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_STRING_HPP
#define X808_STRING_HPP


#include <string>
#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {
	typedef std::string string;

	const char XE_API *findToken(const char *str, const string &token);
	const char XE_API *findToken(const string &str, const string &token);

	string XE_API getBlock(const char *str, const char **outPosition = nullptr);
	string XE_API getBlock(const string &str, uint offset = 0);

	string XE_API getFileName(const string &str, bool includeExt = true);

	string XE_API getStatement(const char *str, const char **outPosition = nullptr);

	std::vector<string> XE_API tokenize(const string &str);
	std::vector<string> XE_API splitString(const string &str, const string &delimiters);
	std::vector<string> XE_API splitString(const string &str, char delimiter);
	std::vector<string> XE_API getLines(const string &str);

	bool XE_API startsWith(const string &str, const string &start);

#ifdef XE_PLATFORM_WINDOWS
	std::wstring XE_API toWstring(const char *str);
	std::wstring XE_API toWstring(const string &str);
	string XE_API toString(const std::wstring &str);
#endif

	void XE_API wcharToUTF8(const uint &wchar, uint &utf8);
}

#endif //X808_STRING_HPP
