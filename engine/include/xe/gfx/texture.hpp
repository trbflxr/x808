//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE_HPP
#define X808_TEXTURE_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/string.hpp>

namespace xe {

	namespace internal {
		class PlatformTexture;
	}

#define MIP_MAP_AUTO static_cast<uint>(-1)
#define ANISOTROPY_AUTO static_cast<uint>(-1)

	struct TextureParameters {
		TextureTarget target;
		PixelInternalFormat internalFormat;
		PixelFormat format;
		PixelType pixelType;
		TextureMinFilter minFilter;
		TextureMagFilter magFilter;
		TextureWrap wrap;

		uint mipMapLevels;
		uint anisotropy;


		explicit TextureParameters(TextureTarget target = TextureTarget::Tex2D,
		                           TextureWrap wrap = TextureWrap::Clamp,
		                           uint mipMapLevels = MIP_MAP_AUTO,
		                           uint anisotropy = ANISOTROPY_AUTO) :
				target(target),
				internalFormat(PixelInternalFormat::Rgba),
				format(PixelFormat::Rgba),
				pixelType(PixelType::UnsignedByte),
				minFilter(TextureMinFilter::LinearMipMapLinear),
				magFilter(TextureMagFilter::Linear),
				wrap(wrap),
				mipMapLevels(mipMapLevels),
				anisotropy(anisotropy) { }

		explicit TextureParameters(TextureTarget target,
		                           PixelInternalFormat internalFormat,
		                           PixelFormat format,
		                           PixelType pixelType,
		                           TextureMinFilter minFilter = TextureMinFilter::Linear,
		                           TextureMagFilter magFilter = TextureMagFilter::Linear,
		                           TextureWrap wrap = TextureWrap::Clamp,
		                           uint mipMapLevels = 0,
		                           uint anisotropy = 0) :
				target(target),
				internalFormat(internalFormat),
				format(format),
				pixelType(pixelType),
				minFilter(minFilter),
				magFilter(magFilter),
				wrap(wrap),
				mipMapLevels(mipMapLevels),
				anisotropy(anisotropy) { }
	};


	class XE_API Texture {
	public:
		explicit Texture(const string &name, uint width, uint height, uint depth,
		                 const TextureParameters &params, bool flip = false);

		explicit Texture(const string &name,
		                 const string &path,
		                 const TextureParameters &params, bool flip = false);

		~Texture();

		void bind(uint slot) const;
		void bindImageUnit(uint index, TextureAccess access, uint level = 0, uint layer = 0) const;
		void unbind(uint slot) const;

		void setData2D(const void *pixels) const;
		byte *getData2D() const;

		void generateMipMaps(const TextureTarget &target);

		void copyTo(const Texture *texture) const;

		const string &getName() const;
		const string &getFilePath() const;

		bool hasTransparency() const;

		uint getWidth() const;
		uint getHeight() const;
		uint getDepth() const;

		uint getHandle() const;

		TextureTarget getTarget() const;
		const TextureParameters &getParams() const;

		uint getMaxMipMap() const;

		inline bool isFlipped() const { return flipped; }
		inline void setFlip(bool flip) { flipped = flip; }

		static uint getMaxMipMap(uint width, uint height);

	private:
		internal::PlatformTexture *texture;

		bool flipped;
	};

}


#endif //X808_TEXTURE_HPP
