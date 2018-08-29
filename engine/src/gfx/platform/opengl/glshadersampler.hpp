//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLSHADERSAMPLER_HPP
#define X808_GLSHADERSAMPLER_HPP


#include <xe/gfx/shadersampler.hpp>
#include <xe/utils/string.hpp>

namespace xe { namespace internal {

	class GLShaderSampler : public ShaderSampler {
	private:
		friend class GLBaseShader;

	public:
		explicit GLShaderSampler(Type type, const string &name, uint count);
		~GLShaderSampler() override = default;

		inline const string &getName() const override { return name; }
		inline uint getLocation() const override { return location; }
		inline uint getCount() const override { return count; }
		inline Type getType() const override { return type; }

		static Type stringToType(const string &type);
		static string typeToString(Type type);
		static bool isTypeStrSampler(const string &type);

	private:
		string name;
		uint location;
		uint count;
		Type type;
	};

}}


#endif //X808_GLSHADERSAMPLER_HPP
