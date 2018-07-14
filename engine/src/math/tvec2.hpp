//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_TVEC2_HPP
#define X808_TVEC2_HPP


#include "xeint.hpp"

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

	template<class T>
	inline tvec2<T>::tvec2(): x(0), y(0) { }

	template<class T>
	inline tvec2<T>::tvec2(T x, T y): x(x), y(y) { }

	template<class T>
	template<typename U>
	inline tvec2<T>::tvec2(const tvec2<U> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) { }


	template<typename T>
	inline tvec2<T> operator-(const tvec2<T> &right) {
		return tvec2<T>(-right.x, -right.y);
	}

	template<class T>
	inline tvec2<T> operator+(const tvec2<T> &left, const tvec2<T> &right) {
		return tvec2<T>(left.x + right.x, left.y + right.y);
	}

	template<class T>
	inline tvec2<T> operator-(const tvec2<T> &left, const tvec2<T> &right) {
		return tvec2<T>(left.x - right.x, left.y - right.y);
	}

	template<class T>
	inline tvec2<T> operator*(const tvec2<T> &left, const tvec2<T> &right) {
		return tvec2<T>(left.x * right.x, left.y * right.y);
	}

	template<class T>
	inline tvec2<T> operator/(const tvec2<T> &left, const tvec2<T> &right) {
		return tvec2<T>(left.x / right.x, left.y / right.y);
	}

	template<class T>
	inline tvec2<T> &operator+=(tvec2<T> &left, const tvec2<T> &right) {
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	template<class T>
	inline tvec2<T> &operator-=(tvec2<T> &left, const tvec2<T> &right) {
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	template<class T>
	inline tvec2<T> &operator*=(tvec2<T> &left, const tvec2<T> &right) {
		left.x *= right.x;
		left.y *= right.y;
		return left;
	}

	template<class T>
	inline tvec2<T> &operator/=(tvec2<T> &left, const tvec2<T> &right) {
		left.x /= right.x;
		left.y /= right.y;
		return left;
	}

	template<class T>
	inline bool operator==(const tvec2<T> &left, const tvec2<T> &right) {
		return left.x == right.x && left.y == right.y;
	}

	template<class T>
	inline bool operator!=(const tvec2<T> &left, const tvec2<T> &right) {
		return (left.x != right.x) || (left.y != right.y);
	}

	typedef xe::tvec2<uint> vec2u;
	typedef xe::tvec2<int32> vec2i;
	typedef xe::tvec2<float> vec2f;
}

#endif //X808_TVEC2_HPP
