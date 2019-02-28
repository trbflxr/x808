//
// Created by FLXR on 8/17/2018.
//

#ifndef X808_SPAK_HPP
#define X808_SPAK_HPP


#include <unordered_map>
#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/string.hpp>

namespace xe {

	class XE_API spak {
	private:
		struct Stamp {
			byte x;
			byte y;
			byte z;
			uint64 count;
		};

		struct ShaderEntry {
			uint64 nameSize;
			uint64 dataSize;
		};


	public:
		static std::unordered_map<string, string> unpackShaders(const string &path);
		static void packShaders(const string &srcPath, const string &destPath);

	private:
		static bool checkStamp(const Stamp &stamp) {
			return stamp.x == 0xDE && stamp.y == 0xAD && stamp.z == 0x22;
		}

		static string getFileName(const string &str, bool includeExt);
	};
}


#endif //X808_SPAK_HPP
