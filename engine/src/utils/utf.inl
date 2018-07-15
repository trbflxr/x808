//
// Created by FLXR on 7/15/2018.
//

template<typename In>
In utf<8>::decode(In begin, In end, uint &output, uint replacement) {
	static const int trailing[256] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
	};
	static const uint offsets[6] = {
			0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
	};

	int trailingBytes = trailing[static_cast<byte>(*begin)];
	if (begin + trailingBytes < end) {
		output = 0;
		switch (trailingBytes) {
			case 5: output += static_cast<byte>(*begin++);
				output <<= 6;
			case 4: output += static_cast<byte>(*begin++);
				output <<= 6;
			case 3: output += static_cast<byte>(*begin++);
				output <<= 6;
			case 2: output += static_cast<byte>(*begin++);
				output <<= 6;
			case 1: output += static_cast<byte>(*begin++);
				output <<= 6;
			case 0: output += static_cast<byte>(*begin++);
		}
		output -= offsets[trailingBytes];
	} else {
		begin = end;
		output = replacement;
	}

	return begin;
}

template<typename Out>
Out utf<8>::encode(uint input, Out output, byte replacement) {
	static const byte firstBytes[7] = {
			0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
	};

	if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF))) {
		if (replacement) {
			*output++ = replacement;
		}
	} else {
		std::size_t bytestoWrite = 1;
		if (input < 0x80) bytestoWrite = 1;
		else if (input < 0x800) bytestoWrite = 2;
		else if (input < 0x10000) bytestoWrite = 3;
		else if (input <= 0x0010FFFF) bytestoWrite = 4;

		byte bytes[4];
		switch (bytestoWrite) {
			case 4: bytes[3] = static_cast<byte>((input | 0x80) & 0xBF);
				input >>= 6;
			case 3: bytes[2] = static_cast<byte>((input | 0x80) & 0xBF);
				input >>= 6;
			case 2: bytes[1] = static_cast<byte>((input | 0x80) & 0xBF);
				input >>= 6;
			case 1: bytes[0] = static_cast<byte> (input | firstBytes[bytestoWrite]);
		}

		output = std::copy(bytes, bytes + bytestoWrite, output);
	}

	return output;
}

template<typename In>
In utf<8>::next(In begin, In end) {
	uint codepoint;
	return decode(begin, end, codepoint);
}

template<typename In>
std::size_t utf<8>::count(In begin, In end) {
	std::size_t length = 0;
	while (begin < end) {
		begin = next(begin, end);
		++length;
	}

	return length;
}

template<typename In, typename Out>
Out utf<8>::fromAnsi(In begin, In end, Out output, const std::locale &locale) {
	while (begin < end) {
		uint codepoint = utf<32>::decodeAnsi(*begin++, locale);
		output = encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::fromWide(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint = utf<32>::decodeWide(*begin++);
		output = encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::fromLatin1(In begin, In end, Out output) {
	while (begin < end)
		output = encode(*begin++, output);

	return output;
}

template<typename In, typename Out>
Out utf<8>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<32>::encodeAnsi(codepoint, output, replacement, locale);
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::toWide(In begin, In end, Out output, wchar_t replacement) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<32>::encodeWide(codepoint, output, replacement);
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::toLatin1(In begin, In end, Out output, char replacement) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		*output++ = codepoint < 256 ? static_cast<char>(codepoint) : replacement;
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::toUtf8(In begin, In end, Out output) {
	return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out utf<8>::toUtf16(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<16>::encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<8>::toUtf32(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		*output++ = codepoint;
	}

	return output;
}

template<typename In>
In utf<16>::decode(In begin, In end, uint &output, uint replacement) {
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
Out utf<16>::encode(uint input, Out output, uint16 replacement) {
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

template<typename In>
In utf<16>::next(In begin, In end) {
	uint codepoint;
	return decode(begin, end, codepoint);
}

template<typename In>
std::size_t utf<16>::count(In begin, In end) {
	std::size_t length = 0;
	while (begin < end) {
		begin = next(begin, end);
		++length;
	}

	return length;
}

template<typename In, typename Out>
Out utf<16>::fromAnsi(In begin, In end, Out output, const std::locale &locale) {
	while (begin < end) {
		uint codepoint = utf<32>::decodeAnsi(*begin++, locale);
		output = encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::fromWide(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint = utf<32>::decodeWide(*begin++);
		output = encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::fromLatin1(In begin, In end, Out output) {
	return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out utf<16>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<32>::encodeAnsi(codepoint, output, replacement, locale);
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::toWide(In begin, In end, Out output, wchar_t replacement) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<32>::encodeWide(codepoint, output, replacement);
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::toLatin1(In begin, In end, Out output, char replacement) {
	while (begin < end) {
		*output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
		begin++;
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::toUtf8(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		output = utf<8>::encode(codepoint, output);
	}

	return output;
}

template<typename In, typename Out>
Out utf<16>::toUtf16(In begin, In end, Out output) {
	return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out utf<16>::toUtf32(In begin, In end, Out output) {
	while (begin < end) {
		uint codepoint;
		begin = decode(begin, end, codepoint);
		*output++ = codepoint;
	}

	return output;
}

template<typename In>
In utf<32>::decode(In begin, In /*end*/, uint &output, uint) {
	output = *begin++;
	return begin;
}

template<typename Out>
Out utf<32>::encode(uint input, Out output, uint) {
	*output++ = input;
	return output;
}

template<typename In>
In utf<32>::next(In begin, In /*end*/) {
	return ++begin;
}

template<typename In>
std::size_t utf<32>::count(In begin, In end) {
	return begin - end;
}

template<typename In, typename Out>
Out utf<32>::fromAnsi(In begin, In end, Out output, const std::locale &locale) {
	while (begin < end)
		*output++ = decodeAnsi(*begin++, locale);

	return output;
}

template<typename In, typename Out>
Out utf<32>::fromWide(In begin, In end, Out output) {
	while (begin < end)
		*output++ = decodeWide(*begin++);

	return output;
}

template<typename In, typename Out>
Out utf<32>::fromLatin1(In begin, In end, Out output) {
	// Latin-1 is directly compatible with Unicode encodings,
	// and can thus be treated as (a sub-range of) UTF-32
	return std::copy(begin, end, output);
}

template<typename In, typename Out>
Out utf<32>::toAnsi(In begin, In end, Out output, char replacement, const std::locale &locale) {
	while (begin < end)
		output = encodeAnsi(*begin++, output, replacement, locale);

	return output;
}

template<typename In, typename Out>
Out utf<32>::toWide(In begin, In end, Out output, wchar_t replacement) {
	while (begin < end)
		output = encodeWide(*begin++, output, replacement);

	return output;
}

template<typename In, typename Out>
Out utf<32>::toLatin1(In begin, In end, Out output, char replacement) {
	// Latin-1 is directly compatible with Unicode encodings,
	// and can thus be treated as (a sub-range of) UTF-32
	while (begin < end) {
		*output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
		begin++;
	}

	return output;
}

template<typename In, typename Out>
Out utf<32>::toUtf8(In begin, In end, Out output) {
	while (begin < end)
		output = utf<8>::encode(*begin++, output);

	return output;
}

template<typename In, typename Out>
Out utf<32>::toUtf16(In begin, In end, Out output) {
	while (begin < end)
		output = utf<16>::encode(*begin++, output);

	return output;
}

template<typename In, typename Out>
Out utf<32>::toUtf32(In begin, In end, Out output) {
	return std::copy(begin, end, output);
}

template<typename In>
uint utf<32>::decodeAnsi(In input, const std::locale &locale) {

#if defined(XE_PLATFORM_WINDOWS) && \
       (defined(__GLIBCPP__) || defined (__GLIBCXX__)) && \
      !(defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

	(void)locale; // to avoid warnings

		wchar_t character = 0;
		mbtowc(&character, &input, 1);
		return static_cast<uint>(character);

#else

	// Get the facet of the locale which deals with character conversion
	const std::ctype<wchar_t> &facet = std::use_facet < std::ctype < wchar_t >> (locale);

	// Use the facet to convert each character of the input string
	return static_cast<uint>(facet.widen(input));

#endif
}

template<typename In>
uint utf<32>::decodeWide(In input) {
	return input;
}


template<typename Out>
Out utf<32>::encodeAnsi(uint codepoint, Out output, char replacement, const std::locale &locale) {

#if defined(XE_PLATFORM_WINDOWS) && \
       (defined(__GLIBCPP__) || defined (__GLIBCXX__)) && \
      !(defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

	(void)locale; // to avoid warnings

		char character = 0;
		if (wctomb(&character, static_cast<wchar_t>(codepoint)) >= 0)
			*output++ = character;
		else if (replacement)
			*output++ = replacement;

		return output;

#else

	// Get the facet of the locale which deals with character conversion
	const std::ctype<wchar_t> &facet = std::use_facet < std::ctype < wchar_t >> (locale);

	// Use the facet to convert each character of the input string
	*output++ = facet.narrow(static_cast<wchar_t>(codepoint), replacement);

	return output;

#endif
}


////////////////////////////////////////////////////////////
template<typename Out>
Out utf<32>::encodeWide(uint codepoint, Out output, wchar_t replacement) {
	switch (sizeof(wchar_t)) {
		case 4: {
			*output++ = static_cast<wchar_t>(codepoint);
			break;
		}

		default: {
			if ((codepoint <= 0xFFFF) && ((codepoint < 0xD800) || (codepoint > 0xDFFF))) {
				*output++ = static_cast<wchar_t>(codepoint);
			} else if (replacement) {
				*output++ = replacement;
			}
			break;
		}
	}

	return output;
}
