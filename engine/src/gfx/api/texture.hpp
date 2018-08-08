//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE_HPP
#define X808_TEXTURE_HPP


#include <string>
#include "common.hpp"
#include "xeint.hpp"

namespace xe { namespace api {

	enum class TextureTarget {
		TEX1D, TEX2D, TEX3D, TEX2D_ARRAY, TEX_CUBE_MAP, TEX_CUBE_MAP_ARRAY
	};

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
		TextureTarget target;
		TextureFormat format;
		TextureFilter filter;
		TextureWrap wrap;

		TextureParameters(TextureTarget target) :
				target(target),
				format(TextureFormat::RGBA),
				filter(TextureFilter::TRILINEAR),
				wrap(TextureWrap::CLAMP) { }

		TextureParameters(TextureTarget target, TextureFormat format, TextureFilter filter, TextureWrap wrap) :
				target(target),
				format(format),
				filter(filter),
				wrap(wrap) { }

		TextureParameters(TextureTarget target, TextureFilter filter) :
				target(target),
				format(TextureFormat::RGBA),
				filter(filter),
				wrap(TextureWrap::CLAMP) { }

		TextureParameters(TextureTarget target, TextureFilter filter, TextureWrap wrap) :
				target(target),
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

	//todo: refactor texture

	class XE_API Texture {
	public:
		virtual ~Texture() = default;

		virtual void bind(uint slot) const = 0;
		virtual void unbind(uint slot) const = 0;

		virtual const std::string &getName() const = 0;
		virtual const std::string &getFilePath() const = 0;

		virtual void setData(const void *pixels) = 0;

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
		virtual uint getDepth() const = 0;

		virtual uint getHandle() const = 0;

		virtual TextureTarget getTarget() const { return target; };

		static Texture *create(uint width, uint height, TextureParameters params);

		static Texture *create(const std::string_view &name,
		                       const std::string_view &path,
		                       TextureParameters params,
		                       TextureLoadOptions options = { });

		static byte getStrideFromFormat(TextureFormat format);
		inline static void setWrap(TextureWrap mode) { wrapMode = mode; }
		inline static void setFilter(TextureFilter mode) { filterMode = mode; }

	protected:
		explicit Texture(TextureTarget target);

	protected:
		TextureTarget target;

		static TextureWrap wrapMode;
		static TextureFilter filterMode;
	};

}}


#endif //X808_TEXTURE_HPP
