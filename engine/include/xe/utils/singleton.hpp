//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_SINGLETON_HPP
#define X808_SINGLETON_HPP


#include <xe/utils/noncopyable.hpp>

namespace xe { namespace utils {

	template<typename T>
	class Singleton : NonCopyable {
	public:
		static T &get() {
			static T instance;
			return instance;
		}
	};

}}


#endif //X808_SINGLETON_HPP
