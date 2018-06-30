//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_COLOR_HPP
#define X808_COLOR_HPP

#include "xeint.hpp"

namespace xe { namespace color {

	static constexpr uint TRANSPARENT = 0x00000000;

	static constexpr uint BLACK = 0xff000000;
	static constexpr uint WHITE = 0xffffffff;
	static constexpr uint RED = 0xff0000ff;
	static constexpr uint GREEN = 0xff00ff00;
	static constexpr uint BLUE = 0xffff0000;

	static constexpr uint YELLOW = 0xff00ffff;
	static constexpr uint CYAN = 0xffffff00;
	static constexpr uint PINK = 0xffff00ff;

	static constexpr uint GRAY = 0xff5a5a5a;
	static constexpr uint LIGHTGRAY = 0xff9a9a9a;

	static constexpr uint rgba(float r, float g, float b, float a) {
		const uint r1 = static_cast<uint>(r * 255);
		const uint g1 = static_cast<uint>(g * 255);
		const uint b1 = static_cast<uint>(b * 255);
		const uint a1 = static_cast<uint>(a * 255);

		const uint color = a1 << 24 | b1 << 16 | g1 << 8 | r1;
		return color;
	}

}}

#endif //X808_COLOR_HPP
