//
// Created by FLXR on 7/4/2018.
//

#include <cstring>
#include "string.hpp"

const char *xe::utils::findToken(const char *str, const std::string_view &token) {
	const char *t = str;
	while ((t = strstr(t, token.data()))) {
		bool left = str == t || isspace(t[-1]);
		bool right = !t[token.size()] || isspace(t[token.size()]);

		if (left && right) return t;

		t += token.size();
	}
	return nullptr;
}

const char *xe::utils::findToken(const std::string_view &str, const std::string_view &token) {
	return findToken(str.data(), token);
}

std::string xe::utils::getBlock(const char *str, const char **outPosition) {
	const char *end = strstr(str, "}");
	if (!end) return std::string(str);

	if (outPosition) *outPosition = end;

	uint length = end - str + 1;
	return std::string(str, length);
}

std::string xe::utils::getBlock(const std::string_view &str, uint offset) {
	const char *s = str.data() + offset;
	return getBlock(s);
}

std::string xe::utils::getStatement(const char *str, const char **outPosition) {
	const char *end = strstr(str, ";");
	if (!end) return std::string(str);

	if (outPosition) *outPosition = end;

	uint length = end - str + 1;
	return std::string(str, length);
}

std::vector<std::string> xe::utils::tokenize(const std::string &string) {
	return splitString(string, " \t\n");
}

std::vector<std::string> xe::utils::splitString(const std::string &string, const std::string &delimiters) {
	size_t start = 0;
	size_t end = string.find_first_of(delimiters);

	std::vector<std::string> result;

	while (end <= std::string::npos) {
		std::string token = string.substr(start, end - start);
		if (!token.empty())
			result.push_back(token);

		if (end == std::string::npos) break;

		start = end + 1;
		end = string.find_first_of(delimiters, start);
	}

	return result;
}

std::vector<std::string> xe::utils::splitString(const std::string &string, char delimiter) {
	return splitString(string, std::string(1, delimiter));
}

std::vector<std::string> xe::utils::getLines(const std::string &string){
	return splitString(string, "\n");
}

bool xe::utils::startsWith(const std::string_view &string, const std::string_view &start) {
	return string.find(start) == 0;
}