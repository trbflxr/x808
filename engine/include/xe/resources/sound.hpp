//
// Created by FLXR on 7/5/2018.
//

#ifndef X808_SOUND_HPP
#define X808_SOUND_HPP


#include <xe/string.hpp>
#include <xe/xeint.hpp>
#include <xe/common.hpp>

struct ga_Sound;
struct ga_Handle;

namespace xe {

	class XE_API Sound {
	private:
		friend void destroyOnFinish(ga_Handle *handle, void *context);
		friend void loopOnFinish(ga_Handle *handle, void *context);

	public:
		explicit Sound(const string &name, const string &path);
		~Sound();

		void play() const;
		void loop() const;
		void pause() const;
		void resume() const;
		void stop() const;

		void setGain(float gain) const;

		inline const string &getName() const { return name; }
		inline const string &getPath() const { return path; }
		inline bool isPlaying() const { return playing; }
		inline float getGain() const { return gain; }

	private:
		string name;
		string path;
		int32 position;

		ga_Sound *sound;

		mutable ga_Handle *handle;
		mutable uint count;
		mutable bool playing;
		mutable float gain;
	};


	void destroyOnFinish(ga_Handle *handle, void *context);
	void loopOnFinish(ga_Handle *handle, void *context);
}


#endif //X808_SOUND_HPP
