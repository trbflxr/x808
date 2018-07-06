//
// Created by FLXR on 6/28/2018.
//

#ifndef X808_SINGLETON_HPP
#define X808_SINGLETON_HPP


#include "common.hpp"

namespace xe { namespace utils {

	template<typename T>
	class XE_API Singleton {
	public:
		virtual ~Singleton() = default;

		NULL_COPY_AND_ASSIGN(Singleton);

		static T &get() {
			static T instance;
			return instance;
		}

	protected:
		Singleton() = default;
	};

}}


#endif //X808_SINGLETON_HPP
