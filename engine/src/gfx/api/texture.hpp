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
		NONE = 0, REPEAT, CLAMP, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
	};

	enum class TextureFilter {
		NONE = 0, LINEAR, NEAREST
	};


	enum class TextureFormat {
		NONE = 0, RGB, RGBA, LUMINANCE, LUMINANCE_ALPHA
	};

	struct TextureParameters {
		TextureFormat format;
		TextureFilter filter;
		TextureWrap wrap;

		TextureParameters() :
				format(TextureFormat::RGBA),
				filter(TextureFilter::LINEAR),
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
				filter(filter), wrap(wrap) { }
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

		virtual std::string_view getName() const = 0;
		virtual std::string_view getFilePath() const = 0;

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
