//
// Created by FLXR on 7/4/2018.
//

#ifndef X808_STRING_HPP
#define X808_STRING_HPP


#include <string>
#include <cstring>
#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {
	typedef std::string string;
	typedef std::wstring wstring;
}

namespace xe { namespace utils {

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

	wstring XE_API toWstring(const char *str);
	wstring XE_API toWstring(const string &str);

}}

//unicode
namespace xe {

	template<uint N>
	struct utf;

	template<>
	struct utf<16> {
		template<typename In>
		static In decode(In begin, In end, uint &output, uint replacement = 0) {
			uint16 first = *begin++;

			if ((first >= 0xD800) && (first <= 0xDBFF)) {
				if (begin < end) {
					uint second = *begin++;
					if ((second >= 0xDC00) && (second <= 0xDFFF)) {
						output = static_cast<uint>(((first - 0xD800) << 10) + (second - 0xDC00) + 0x0010000);
					} else {
						output = replacement;
					}
				} else {
					begin = end;
					output = replacement;
				}
			} else {
				output = first;
			}

			return begin;
		}

		template<typename Out>
		static Out encode(uint input, Out output, uint16 replacement = 0) {
			if (input <= 0xFFFF) {
				if ((input >= 0xD800) && (input <= 0xDFFF)) {
					if (replacement)
						*output++ = replacement;
				} else {
					*output++ = static_cast<uint16>(input);
				}
			} else if (input > 0x0010FFFF) {
				if (replacement)
					*output++ = replacement;
			} else {
				input -= 0x0010000;
				*output++ = static_cast<uint16>((input >> 10) + 0xD800);
				*output++ = static_cast<uint16>((input & 0x3FFUL) + 0xDC00);
			}

			return output;
		}

		template<typename In, typename Out>
		static Out toUtf32(In begin, In end, Out output) {
			while (begin < end) {
				uint codepoint;
				begin = decode(begin, end, codepoint);
				*output++ = codepoint;
			}

			return output;
		}
	};

	typedef utf<16> utf16;

}

#endif //X808_STRING_HPP
