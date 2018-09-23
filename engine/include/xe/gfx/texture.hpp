//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE_HPP
#define X808_TEXTURE_HPP


#include <xe/common.hpp>
#include <xe/xeint.hpp>
#include <xe/gfx/enums.hpp>
#include <xe/utils/string.hpp>

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

	struct TextureLoadOptions {
		bool flipX;
		bool flipY;

		TextureLoadOptions() : flipX(false), flipY(false) { }
		TextureLoadOptions(bool flipX, bool flipY) : flipX(flipX), flipY(flipY) { }
	};

	class XE_API Texture {
	public:
		explicit Texture(const string &name, uint width, uint height, uint depth, const TextureParameters &params);

		explicit Texture(const string &name,
		                 const wstring &path,
		                 const TextureParameters &params,
		                 bool hasTransparency = false,
		                 const TextureLoadOptions &options = { });

		~Texture();

		void bind(uint slot) const;
		void bindImageUnit(uint index, TextureAccess access, uint level = 0, uint layer = 0) const;
		void unbind(uint slot) const;

		void setData2D(const void *pixels) const;

		void generateMipMaps(const TextureTarget &target);

		void copyTo(const Texture *texture) const;

		const string &getName() const;
		const wstring &getFilePath() const;

		uint getWidth() const;
		uint getHeight() const;
		uint getDepth() const;

		uint getHandle() const;

		TextureTarget getTarget() const;

		uint getMaxMipMap() const;

		bool hasTransparency() const;

		static uint getMaxMipMap(uint width, uint height);

	private:
		internal::PlatformTexture *texture;
	};

}


#endif //X808_TEXTURE_HPP
