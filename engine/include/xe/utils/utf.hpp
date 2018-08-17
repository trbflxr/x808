//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_UTF_HPP
#define X808_UTF_HPP

#include <locale>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <xe/xeint.hpp>

namespace xe {
	template<uint N>
	struct utf;

	template<>
	struct utf<8> {
		template<typename In>
		static In decode(In begin, In end, uint &output, uint replacement = 0);
		template<typename Out>
		static Out encode(uint input, Out output, byte replacement = 0);

		template<typename In>
		static In next(In begin, In end);

		template<typename In>
		static std::size_t count(In begin, In end);

		template<typename In, typename Out>
		static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out fromWide(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out fromLatin1(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out
		toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

		template<typename In, typename Out>
		static Out toLatin1(In begin, In end, Out output, char replacement = 0);

		template<typename In, typename Out>
		static Out toUtf8(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf16(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf32(In begin, In end, Out output);
	};

	template<>
	struct utf<16> {
		template<typename In>
		static In decode(In begin, In end, uint &output, uint replacement = 0);

		template<typename Out>
		static Out encode(uint input, Out output, uint16 replacement = 0);

		template<typename In>
		static In next(In begin, In end);

		template<typename In>
		static std::size_t count(In begin, In end);

		template<typename In, typename Out>
		static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out fromWide(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out fromLatin1(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

		template<typename In, typename Out>
		static Out toLatin1(In begin, In end, Out output, char replacement = 0);

		template<typename In, typename Out>
		static Out toUtf8(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf16(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf32(In begin, In end, Out output);
	};

	template<>
	struct utf<32> {
		template<typename In>
		static In decode(In begin, In end, uint &output, uint replacement = 0);

		template<typename Out>
		static Out encode(uint input, Out output, uint replacement = 0);

		template<typename In>
		static In next(In begin, In end);

		template<typename In>
		static std::size_t count(In begin, In end);

		template<typename In, typename Out>
		static Out fromAnsi(In begin, In end, Out output, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out fromWide(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out fromLatin1(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale &locale = std::locale());

		template<typename In, typename Out>
		static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

		template<typename In, typename Out>
		static Out toLatin1(In begin, In end, Out output, char replacement = 0);

		template<typename In, typename Out>
		static Out toUtf8(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf16(In begin, In end, Out output);

		template<typename In, typename Out>
		static Out toUtf32(In begin, In end, Out output);

		template<typename In>
		static uint decodeAnsi(In input, const std::locale &locale = std::locale());

		template<typename In>
		static uint decodeWide(In input);

		template<typename Out>
		static Out encodeAnsi(uint codepoint, Out output, char replacement = 0, const std::locale &locale = std::locale());

		template<typename Out>
		static Out encodeWide(uint codepoint, Out output, wchar_t replacement = 0);
	};

#include <xe/utils/utf.inl>

	typedef utf<8> utf8;
	typedef utf<16> utf16;
	typedef utf<32> utf32;
}

#endif //X808_UTF_HPP
