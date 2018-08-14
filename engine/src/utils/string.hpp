//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_STRING_HPP
#define X808_STRING_HPP


#include <string>
#include <vector>
#include "xeint.hpp"

namespace xe { namespace utils {

	const char *findToken(const char *str, const std::string_view &token);
	const char *findToken(const std::string_view &str, const std::string_view &token);

	std::string getBlock(const char *str, const char **outPosition = nullptr);
	std::string getBlock(const std::string_view &str, uint offset = 0);

	std::string getFileName(const std::string_view &str, bool includeExt = true);

	std::string getStatement(const char *str, const char **outPosition = nullptr);

	std::vector<std::string> tokenize(const std::string &string);
	std::vector<std::string> splitString(const std::string &string, const std::string &delimiters);
	std::vector<std::string> splitString(const std::string &string, char delimiter);
	std::vector<std::string> getLines(const std::string &string);

	bool startsWith(const std::string_view &string, const std::string_view &start);

}}

#endif //X808_STRING_HPP
