//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOSOURCE_HPP
#define X808_AUDIOSOURCE_HPP


#include <xe/math/vec3.hpp>
#include <xe/resources/sound.hpp>

namespace xe {

	class XE_API AudioSource {
	public:
		explicit AudioSource(const string &name, const Sound *sound);
		virtual ~AudioSource();

		void play() const;

		void bindSound(const Sound *sound) const;

		inline const Sound *getSound() const { return sound; }
		inline uint getHandle() const { return handle; }

		inline const string &getName() const { return name; }

	private:
		string name;
		const Sound *sound;

		uint handle;
	};

}


#endif //X808_AUDIOSOURCE_HPP
