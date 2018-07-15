//
// Created by FLXR on 7/14/2018.
//

#include <algorithm>
#include "videomode.hpp"

namespace xe {

	VideoMode::VideoMode() :
			width(0),
			height(0),
			bitsPerPixel(0) { }

	VideoMode::VideoMode(uint width, uint height, uint bitsPerPixel) :
			width(width),
			height(height),
			bitsPerPixel(bitsPerPixel) { }

	bool VideoMode::isValid() const {
		const std::vector<VideoMode> &modes = getFullscreenModes();
		return std::find(modes.begin(), modes.end(), *this) != modes.end();
	}

	bool operator==(const VideoMode &left, const VideoMode &right) {
		return (left.width == right.width) &&
		       (left.height == right.height) &&
		       (left.bitsPerPixel == right.bitsPerPixel);
	}

	bool operator!=(const VideoMode &left, const VideoMode &right) {
		return !(left == right);
	}

	bool operator<(const VideoMode &left, const VideoMode &right) {
		if (left.bitsPerPixel == right.bitsPerPixel) {
			if (left.width == right.width) {
				return left.height < right.height;
			} else {
				return left.width < right.width;
			}
		} else {
			return left.bitsPerPixel < right.bitsPerPixel;
		}
	}

	bool operator>(const VideoMode &left, const VideoMode &right) {
		return right < left;
	}


	bool operator<=(const VideoMode &left, const VideoMode &right) {
		return !(right < left);
	}

	bool operator>=(const VideoMode &left, const VideoMode &right) {
		return !(left < right);
	}

}