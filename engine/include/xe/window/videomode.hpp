//
// Created by FLXR on 7/14/2018.
//

#ifndef X808_VIDEOMODE_HPP
#define X808_VIDEOMODE_HPP


#include <vector>
#include <xe/common.hpp>
#include <xe/xeint.hpp>

namespace xe {

	struct XE_API VideoMode {
		VideoMode();
		explicit VideoMode(uint width, uint height, uint bitsPerPixel = 32);

		static VideoMode getDesktopMode();

		static const std::vector<VideoMode> &getFullscreenModes();

		bool isValid() const;

		uint width;
		uint height;
		uint bitsPerPixel;
	};

	bool XE_API operator==(const VideoMode &left, const VideoMode &right);
	bool XE_API operator!=(const VideoMode &left, const VideoMode &right);
	bool XE_API operator<(const VideoMode &left, const VideoMode &right);
	bool XE_API operator>(const VideoMode &left, const VideoMode &right);
	bool XE_API operator<=(const VideoMode &left, const VideoMode &right);
	bool XE_API operator>=(const VideoMode &left, const VideoMode &right);
}


#endif //X808_VIDEOMODE_HPP
