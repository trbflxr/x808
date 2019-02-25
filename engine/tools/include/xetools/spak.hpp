//
// Created by FLXR on 8/17/2018.
//

#ifndef X808_SPAK_HPP
#define X808_SPAK_HPP


#include <string>
#include <unordered_map>
#include <xe/xeint.hpp>
#include <xe/common.hpp>

namespace xe {

	class XE_API spak {
	private:
		enum class FileType {
			Shaders,
			Textures,
			Invalid
		};

		struct Stamp {
			byte x;
			byte y;
			byte z;
			uint64 count;
		};

		struct ShaderStamp {
			const byte x = 0xDE;
			const byte y = 0xAD;
			const byte z = 0x22;
			uint64 count;
		};

		struct TextureStamp {
			const byte x = 0xDE;
			const byte y = 0xAD;
			const byte z = 0x21;
			uint64 count;
		};

		struct ShaderEntry {
			uint64 nameSize;
			uint64 dataSize;
		};

	public:
		static std::unordered_map<std::string, std::string> unpackShaders(const std::string &path);
		static void packShaders(const std::string &srcPath, const std::string &destPath);

		static void test();

	private:
		static FileType checkStamp(const Stamp &stamp);

		static std::string getFileName(const std::string &str, bool includeExt);
	};
}


#endif //X808_SPAK_HPP
