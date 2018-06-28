//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_TVEC2_HPP
#define X808_TVEC2_HPP


namespace xe {
	namespace math {

		template<class T>
		struct tvec2 {
			T x, y;

			tvec2<T>();
			tvec2<T>(const T &x, const T &y);
		};

//		 tvec2<T> operator+(const tvec2<T> &left, const tvec2<T> &right);
//		 tvec2<T> operator-(const tvec2<T> &left, const tvec2<T> &right);
//		 tvec2<T> operator*(const tvec2<T> &left, const tvec2<T> &right);
//		 tvec2<T> operator/(const tvec2<T> &left, const tvec2<T> &right);
//
//		bool operator==(const tvec2<T> &left, const tvec2<T> &right);
//		bool operator!=(const tvec2<T> &left, const tvec2<T> &right);
//
//		tvec2<T> &operator+=(tvec2<T> &left, const tvec2<T> &right);
//		tvec2<T> &operator-=(tvec2<T> &left, const tvec2<T> &right);
//		tvec2<T> &operator*=(tvec2<T> &left, const tvec2<T> &right);
//		tvec2<T> &operator/=(tvec2<T> &left, const tvec2<T> &right);

		template<class T>
		tvec2<T>::tvec2(): x(0), y(0) { }

		template<class T>
		tvec2<T>::tvec2(const T &x, const T &y) : x(x), y(y) { }


		template<class T>
		tvec2<T> operator+(const tvec2<T> &left, const tvec2<T> &right) {
			return tvec2<T>(left.x + right.x, left.y + right.y);
		}

		template<class T>
		tvec2<T> operator-(const tvec2<T> &left, const tvec2<T> &right) {
			return tvec2<T>(left.x - right.x, left.y - right.y);
		}

		template<class T>
		tvec2<T> operator*(const tvec2<T> &left, const tvec2<T> &right) {
			return tvec2<T>(left.x * right.x, left.y * right.y);
		}

		template<class T>
		tvec2<T> operator/(const tvec2<T> &left, const tvec2<T> &right) {
			return tvec2<T>(left.x / right.x, left.y / right.y);
		}

		template<class T>
		tvec2<T> &operator+=(tvec2<T> &left, const tvec2<T> &right) {
			left.x += right.x;
			left.y += right.y;
			return left;
		}

		template<class T>
		tvec2<T> &operator-=(tvec2<T> &left, const tvec2<T> &right) {
			left.x -= right.x;
			left.y -= right.y;
			return left;
		}

		template<class T>
		tvec2<T> &operator*=(tvec2<T> &left, const tvec2<T> &right) {
			left.x *= right.x;
			left.y *= right.y;
			return left;
		}

		template<class T>
		tvec2<T> &operator/=(tvec2<T> &left, const tvec2<T> &right) {
			left.x /= right.x;
			left.y /= right.y;
			return left;
		}

		template<class T>
		bool operator==(const tvec2<T> &left, const tvec2<T> &right) {
			return left.x == right.x && left.y == right.y;
		}

		template<class T>
		bool operator!=(const tvec2<T> &left, const tvec2<T> &right) {
			return (left.x != right.x) || (left.y != right.y);
		}

	}

	typedef xe::math::tvec2<uint> vec2u;
}

#endif //X808_TVEC2_HPP
