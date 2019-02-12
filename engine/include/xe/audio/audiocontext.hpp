//
// Created by FLXR on 2/12/2019.
//

#ifndef X808_AUDIOCONTEXT_HPP
#define X808_AUDIOCONTEXT_HPP


#include <xe/common.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class XE_API AudioContext : NonCopyable {
	public:
		static void create();

	private:
		static AudioContext &instance();

		~AudioContext() override;

	private:
		void *context;
		void *device;
	};


}


#endif //X808_AUDIOCONTEXT_HPP
