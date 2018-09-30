//
// Created by FLXR on 7/15/2018.
//

#ifndef X808_CURSOR_HPP
#define X808_CURSOR_HPP


#include <xe/xeint.hpp>
#include <xe/math/vec2.hpp>
#include <xe/utils/noncopyable.hpp>

namespace xe {

	class Cursor : NonCopyable {
	private:
		friend class PlatformWindowWin32;

	public:
		enum Type {
			Arrow,
			ArrowWait,
			Wait,
			Text,
			Hand,
			SizeHorizontal,
			SizeVertical,
			SizeTopLeftBottomRight,
			SizeBottomLeftTopRight,
			SizeAll,
			Cross,
			Help,
			NotAllowed
		};

	public:
		explicit Cursor(const byte *pixels, vec2 size, vec2 hotspot);
		explicit Cursor(Type type);
		~Cursor() override;

		inline void *raw() const { return cursor; }
	private:
		void release();

	private:
		void *cursor;
	};

}


#endif //X808_CURSOR_HPP
