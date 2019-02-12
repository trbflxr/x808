//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_SOUND_HPP
#define X808_SOUND_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/string.hpp>

namespace xe {

	class XE_API Sound final {
	public:
		enum class Format {
			Mono8,
			Mono16,
			Stereo8,
			Stereo16,
			Invalid
		};

	public:
		explicit Sound(const string &name, const string &file);
		~Sound();

		inline const uint getHandle() const { return handle; }

		inline Format getFormat() const { return format; }
		inline uint getSize() const { return size; }
		inline uint getFreq() const { return freq; }
		inline uint16 getChannels() const { return channels; }
		inline uint16 getBps() const { return bps; }

		inline const string &getName() const { return name; }

	private:
		friend class AudioLoader;

		const string name;

		uint handle;
		Format format;
		uint size;
		uint freq;
		uint16 channels;
		uint16 bps;
	};

}


#endif //X808_SOUND_HPP
