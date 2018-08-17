//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_TVEC2_HPP
#define X808_TVEC2_HPP


#include <cmath>
#include <xe/xeint.hpp>

namespace xe {

	template<class T>
	struct tvec2 {
		T x;
		T y;

		inline tvec2();
		inline tvec2(T x, T y);

		template<typename U>
		inline explicit tvec2(const tvec2<U> &other);
	};

#include "tvec2.inl"

	typedef xe::tvec2<uint> vec2u;
	typedef xe::tvec2<int32> vec2i;
	typedef xe::tvec2<float> vec2f;
}

#endif //X808_TVEC2_HPP
