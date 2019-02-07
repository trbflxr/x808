//
// Created by FLXR on 8/17/2018.
//

#ifndef X808_SPAK_HPP
#define X808_SPAK_HPP


#include <string>
#include <unordered_map>
#include <xe/xeint.hpp>

namespace xe { namespace spak {

	struct Stamp {
		const byte x = 0xDE;
		const byte y = 0xAD;
		const byte z = 0x22;
		uint64 count;
	};

	struct ShaderEntry {
		uint64 nameSize;
		uint64 dataSize;
	};

	inline bool checkStamp(const Stamp &stamp) {
		return stamp.x == 0xDE && stamp.y == 0xAD && stamp.z == 0x22;
	}

	std::unordered_map<std::string, std::string> unpack(const std::string &path);

	void pack(const std::string &srcPath, const std::string &destPath);

}}


#endif //X808_SPAK_HPP
