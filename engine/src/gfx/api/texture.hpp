//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE_HPP
#define X808_TEXTURE_HPP


#include <string>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace gfx { namespace api {

	enum class TextureWrap {
		REPEAT = 0, CLAMP, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
	};

	enum class TextureFilter {
		NEAREST = 0, BILINEAR, TRILINEAR, AF2, AF4, AF8, AF16
	};


	enum class TextureFormat {
		RGB = 0, RGBA, LUMINANCE, LUMINANCE_ALPHA, DEPTH16, DEPTH24, RG32F
	};

	struct TextureParameters {
		TextureFormat format;
		TextureFilter filter;
		TextureWrap wrap;

		TextureParameters() :
				format(TextureFormat::RGBA),
				filter(TextureFilter::TRILINEAR),
				wrap(TextureWrap::CLAMP) { }

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap) :
				format(format),
				filter(filter),
				wrap(wrap) { }

		TextureParameters(TextureFilter filter) :
				format(TextureFormat::RGBA),
				filter(filter),
				wrap(TextureWrap::CLAMP) { }

		TextureParameters(TextureFilter filter, TextureWrap wrap) :
				format(TextureFormat::RGBA),
				filter(filter),
				wrap(wrap) { }
	};

	struct TextureLoadOptions {
		bool flipX;
		bool flipY;

		TextureLoadOptions() : flipX(false), flipY(false) { }
		TextureLoadOptions(bool flipX, bool flipY) : flipX(flipX), flipY(flipY) { }
	};

	class XE_API Texture {
	public:
		virtual ~Texture() = default;

		virtual void bind(uint slot) const = 0;
		virtual void unbind(uint slot) const = 0;

		virtual const std::string &getName() const = 0;
		virtual const std::string &getFilePath() const = 0;

		virtual uint getHandle() const = 0;

		static byte getStrideFromFormat(TextureFormat format);

		inline static void setWrap(TextureWrap mode) { wrapMode = mode; }
		inline static void setFilter(TextureFilter mode) { filterMode = mode; }

	protected:
		static TextureWrap wrapMode;
		static TextureFilter filterMode;
	};

}}}


#endif //X808_TEXTURE_HPP
