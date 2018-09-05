//
// Created by FLXR on 7/15/2018.
//

template<class T>
inline tvec2<T>::tvec2(): x(0), y(0) { }

template<class T>
inline tvec2<T>::tvec2(T x, T y): x(x), y(y) { }

template<class T>
template<typename U>
inline tvec2<T>::tvec2(const tvec2 <U> &other): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) { }

template<typename T>
inline tvec2 <T> operator-(const tvec2 <T> &right) {
	return tvec2<T>(-right.x, -right.y);
}

template<class T>
inline tvec2 <T> operator+(const tvec2 <T> &left, const tvec2 <T> &right) {
	return tvec2<T>(left.x + right.x, left.y + right.y);
}

template<class T>
inline tvec2 <T> operator-(const tvec2 <T> &left, const tvec2 <T> &right) {
	return tvec2<T>(left.x - right.x, left.y - right.y);
}

template<class T>
inline tvec2 <T> operator*(const tvec2 <T> &left, T right) {
	return tvec2<T>(left.x * right, left.y * right);
}

template<class T>
inline tvec2 <T> operator*(const tvec2 <T> &left, const tvec2 <T> &right) {
	return tvec2<T>(left.x * right.x, left.y * right.y);
}

template<class T>
inline tvec2 <T> operator/(const tvec2 <T> &left, T right) {
	return tvec2<T>(left.x / right, left.y / right);
}

template<class T>
inline tvec2 <T> operator/(const tvec2 <T> &left, const tvec2 <T> &right) {
	return tvec2<T>(left.x / right.x, left.y / right.y);
}

template<class T>
inline tvec2 <T> &operator+=(tvec2 <T> &left, const tvec2 <T> &right) {
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<class T>
inline tvec2 <T> &operator-=(tvec2 <T> &left, const tvec2 <T> &right) {
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<class T>
inline tvec2 <T> &operator*=(tvec2 <T> &left, const tvec2 <T> &right) {
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

template<class T>
inline tvec2 <T> &operator/=(tvec2 <T> &left, const tvec2 <T> &right) {
	left.x /= right.x;
	left.y /= right.y;
	return left;
}

template<class T>
inline bool operator==(const tvec2 <T> &left, const tvec2 <T> &right) {
	return left.x == right.x && left.y == right.y;
}

template<class T>
inline bool operator!=(const tvec2 <T> &left, const tvec2 <T> &right) {
	return (left.x != right.x) || (left.y != right.y);
}