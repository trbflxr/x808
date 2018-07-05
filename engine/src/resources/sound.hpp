//
// Created by FLXR on 7/5/2018.
//

#ifndef X808_SOUND_HPP
#define X808_SOUND_HPP


#include <string>
#include "common.hpp"
#include "xeint.hpp"

struct ga_Sound;
struct ga_Handle;

namespace xe {

	class XE_API Sound {
	private:
		friend void destroyOnFinish(ga_Handle *handle, void *context);
		friend void loopOnFinish(ga_Handle *handle, void *context);

	public:
		explicit Sound(const std::string_view &name, const std::string_view &path);
		~Sound();

		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setGain(float gain);

		inline const std::string &getName() const { return name; }
		inline const std::string &getPath() const { return path; }
		inline bool isPlaying() const { return playing; }
		inline float getGain() const { return gain; }

	private:
		std::string name;
		std::string path;
		uint count;

		ga_Sound *sound;
		ga_Handle *handle;
		int32 position;

		bool playing;
		float gain;
	};


	void destroyOnFinish(ga_Handle *handle, void *context);
	void loopOnFinish(ga_Handle *handle, void *context);
}


#endif //X808_SOUND_HPP
