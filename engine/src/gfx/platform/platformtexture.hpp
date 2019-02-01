//
// Created by FLXR on 8/16/2018.
//

#ifndef X808_PLATFORMTEXTURE_HPP
#define X808_PLATFORMTEXTURE_HPP

#include <xe/xeint.hpp>
#include <xe/gfx/texture.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/math/math.hpp>

namespace xe { namespace internal {

	class PlatformTexture {
	public:
		virtual ~PlatformTexture() = default;

		virtual void bind(uint slot) const = 0;
		virtual void bindImageUnit(uint index, TextureAccess access, uint level, uint layer) const = 0;
		virtual void unbind(uint slot) const = 0;

		virtual void setData2D(const void *pixels) const = 0;

		virtual void generateMipMaps(const TextureTarget &target) = 0;

		virtual void copyTo(const Texture *texture) const = 0;

		virtual uint getHandle() const = 0;
		virtual const string &getName() const = 0;
		virtual const string &getFilePath() const = 0;

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
		virtual uint getDepth() const = 0;

		virtual TextureTarget getTarget() const = 0;
		virtual const TextureParameters &getParams() const = 0;

		virtual uint getMaxMipMap() const = 0;
	};

}}

#endif //X808_PLATFORMTEXTURE_HPP
