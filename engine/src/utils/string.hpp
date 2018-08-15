//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_STRING_HPP
#define X808_STRING_HPP


#include <string>
#include <vector>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace utils {

	const char XE_API *findToken(const char *str, const std::string_view &token);
	const char XE_API *findToken(const std::string_view &str, const std::string_view &token);

	std::string XE_API getBlock(const char *str, const char **outPosition = nullptr);
	std::string XE_API getBlock(const std::string_view &str, uint offset = 0);

	std::string XE_API getFileName(const std::string_view &str, bool includeExt = true);

	std::string XE_API getStatement(const char *str, const char **outPosition = nullptr);

	std::vector<std::string> XE_API tokenize(const std::string &string);
	std::vector<std::string> XE_API splitString(const std::string &string, const std::string &delimiters);
	std::vector<std::string> XE_API splitString(const std::string &string, char delimiter);
	std::vector<std::string> XE_API getLines(const std::string &string);

	bool XE_API startsWith(const std::string_view &string, const std::string_view &start);

}}

#endif //X808_STRING_HPP
