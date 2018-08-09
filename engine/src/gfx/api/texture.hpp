//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE_HPP
#define X808_TEXTURE_HPP


#include <string>
#include "common.hpp"
#include "xeint.hpp"
#include "enums.hpp"

namespace xe { namespace api {

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


		explicit TextureParameters(TextureTarget target) :
				target(target),
				internalFormat(PixelInternalFormat::Rgba),
				format(PixelFormat::Rgba),
				pixelType(PixelType::UnsignedByte),
				minFilter(TextureMinFilter::LinearMipMapLinear),
				magFilter(TextureMagFilter::Linear),
				wrap(TextureWrap::Clamp),
				mipMapLevels(MIP_MAP_AUTO),
				anisotropy(ANISOTROPY_AUTO) { }

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
		virtual ~Texture() = default;

		virtual void bind(uint slot) const = 0;
		virtual void bindImageUnit(uint slot, uint index, TextureAccess access, uint level, uint layer) const = 0;
		virtual void unbind(uint slot) const = 0;

		virtual void setData2D(const void *pixels) = 0;

		virtual void generateMipMaps(const TextureTarget &target) = 0;

		inline const std::string &getName() const { return name; }
		inline const std::string &getFilePath() const { return fileName; }

		inline virtual uint getWidth() const { return width; };
		inline virtual uint getHeight() const { return height; };
		inline virtual uint getDepth() const { return depth; };
		inline virtual uint getHandle() const { return handle; };
		inline virtual TextureTarget getTarget() const { return params.target; };

		inline uint getMaxMipMap() const { return getMaxMipMap(width, height); }

		static Texture *create(uint width, uint height, uint depth, const TextureParameters &params);

		static Texture *create(const std::string_view &name,
		                       const std::string_view &path,
		                       const TextureParameters &params,
		                       const TextureLoadOptions &options = { });

		static uint getMaxMipMap(uint width, uint height);

	protected:
		explicit Texture(const std::string_view &name,
		                 const std::string_view &path,
		                 uint width, uint height, uint depth,
		                 const TextureParameters &params);

	protected:
		std::string name;
		std::string fileName;

		uint handle;

		uint width;
		uint height;
		uint depth;

		TextureParameters params;

		uint maxMipMapLevels;
		uint maxAnisotropy;
	};

}}


#endif //X808_TEXTURE_HPP
