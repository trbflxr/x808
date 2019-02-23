//
// Created by FLXR on 2/23/2019.
//

#include <xe/utils/random.hpp>
#include <xe/common.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>
#include <xe/math/vec4.hpp>
#include <ctime>

namespace xe {

	random::random()
			: mt(static_cast<uint64>(time(nullptr))) { }

	random &random::get() {
		static random r;
		return r;
	}

	template<>
	XE_API float random::next(const float &low, const float &high) {
		auto bounds = std::uniform_real_distribution<float>(low, high);
		return bounds(get().mt);
	}

	template<>
	XE_API uint random::next(const uint &low, const uint &high) {
		auto bounds = std::uniform_int_distribution<uint>(low, high);
		return bounds(get().mt);
	}

	template<>
	XE_API int32 random::next(const int32 &low, const int32 &high) {
		auto bounds = std::uniform_int_distribution<int32>(low, high);
		return bounds(get().mt);
	}

	template<>
	XE_API vec2 random::next(const vec2 &low, const vec2 &high) {
		auto bx = std::uniform_real_distribution<float>(low.x, high.x);
		auto by = std::uniform_real_distribution<float>(low.y, high.y);
		return vec2(bx(get().mt), by(get().mt));
	}

	template<>
	XE_API vec3 random::next(const vec3 &low, const vec3 &high) {
		auto bx = std::uniform_real_distribution<float>(low.x, high.x);
		auto by = std::uniform_real_distribution<float>(low.y, high.y);
		auto bz = std::uniform_real_distribution<float>(low.z, high.z);
		return vec3(bx(get().mt), by(get().mt), bz(get().mt));
	}

	template<>
	XE_API vec4 random::next(const vec4 &low, const vec4 &high) {
		auto bx = std::uniform_real_distribution<float>(low.x, high.x);
		auto by = std::uniform_real_distribution<float>(low.y, high.y);
		auto bz = std::uniform_real_distribution<float>(low.z, high.z);
		auto bw = std::uniform_real_distribution<float>(low.w, high.w);
		return vec4(bx(get().mt), by(get().mt), bz(get().mt), bw(get().mt));
	}

}