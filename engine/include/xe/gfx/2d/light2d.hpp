//
// Created by FLXR on 9/7/2018.
//

#ifndef X808_LIGHT2D_HPP
#define X808_LIGHT2D_HPP


#include <xe/common.hpp>
#include <xe/utils/string.hpp>
#include <xe/math/vec2.hpp>
#include <xe/math/vec3.hpp>

namespace xe {

	class XE_API Light2D {
	private:
		struct Data {
			vec2 position;
			vec3 color;
			float intensity;

			Data(const vec2 &pos, const vec3 &color, float intensity) :
					position(pos), color(color), intensity(intensity) { }
		};

	public:
		inline explicit Light2D(const string &name, const vec2 &pos, const vec3 &color, float intensity) :
				name(name),
				data(pos, color, intensity) { }

		inline void move(const vec2 &dir) { data.position += dir; }

		inline const string &getName() const { return name; }

		inline const vec2 &getPosition() const { return data.position; }
		inline void setPosition(const vec2 &position) { data.position = position; }

		inline const vec3 &getColor() const { return data.color; }
		inline void setColor(const vec3 &color) { data.color = color; }

		inline float getIntensity() const { return data.intensity; }
		inline void setIntensity(float intensity) { data.intensity = intensity; }

		inline const void *getData() const { return &data; }
		inline static uint getDataSize() { return sizeof(Data); }

	private:
		string name;

		Data data;
	};

}


#endif //X808_LIGHT2D_HPP
