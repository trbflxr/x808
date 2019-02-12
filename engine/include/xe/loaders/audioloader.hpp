//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOLOADER_HPP
#define X808_AUDIOLOADER_HPP


#include <xe/xeint.hpp>
#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>
#include <xe/string.hpp>
#include <xe/resources/sound.hpp>

namespace xe {

	class XE_API AudioLoader : NonCopyable {
	public:
		static byte *load(const string &file, Sound *sound);
		static byte *load(const char *file, Sound *sound);

		static byte *loadWav(const byte *memory, Sound *sound);

	private:
		static constexpr const char *basePath = u8"/audio/";
	};

}

#endif //X808_AUDIOLOADER_HPP
