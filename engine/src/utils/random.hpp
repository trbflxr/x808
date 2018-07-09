//
// Created by FLXR on 7/9/2018.
//

#ifndef X808_RANDOM_HPP
#define X808_RANDOM_HPP


#include <random>
#include <ctime>
#include "xeint.hpp"

namespace xe {

	class random {
	public:
		static int32 nextInt32(int32 low, int32 high) {
			auto bounds = std::uniform_int_distribution<int32>(low, high);
			return bounds(get().mt);
		}

		static uint nextUint(uint low, uint high) {
			auto bounds = std::uniform_int_distribution<uint>(low, high);
			return bounds(get().mt);
		}

		static float nextFloat(float low, float high) {
			auto bounds = std::uniform_real_distribution<float>(low, high);
			return bounds(get().mt);
		}

	private:
		random() : mt(static_cast<uint64>(time(nullptr))) { }

		static random &get() {
			static random r;
			return r;
		}

	private:
		std::mt19937_64 mt;

	};

}


#endif //X808_RANDOM_HPP
