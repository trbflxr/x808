//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLTEXTURE2D_HPP
#define X808_GLTEXTURE2D_HPP


#include <gfx/platform/platformtexture.hpp>

namespace xe { namespace internal {

	class GLTexture : public PlatformTexture {
	public:
		explicit GLTexture(const string &name, uint width, uint height, uint depth, const TextureParameters &params);

		explicit GLTexture(const string &name,
		                   const string &path,
		                   const TextureParameters &params,
		                   const TextureLoadOptions &options);

		~GLTexture() override;

		void bind(uint slot) const override;
		void bindImageUnit(uint slot, uint index, TextureAccess access, uint level, uint layer) const override;
		void unbind(uint slot) const override;

		void setData2D(const void *pixels) override;

		void generateMipMaps(const TextureTarget &target) override;

		inline uint getHandle() const override { return handle; }
		inline const string &getName() const override { return name; }
		inline const string &getFilePath() const override { return fileName; }

		inline uint getWidth() const override { return width; };
		inline uint getHeight() const override { return height; };
		inline uint getDepth() const override { return depth; };
		inline TextureTarget getTarget() const override { return params.target; };

		inline uint getMaxMipMap() const override { return Texture::getMaxMipMap(width, height); }

	private:
		uint loadInternal(const TextureLoadOptions *options);
		byte *loadFromFile(bool &fail, const TextureLoadOptions *options);
		void setTextureParams(const TextureTarget &target);

	private:
		string name;
		string fileName;

		uint width;
		uint height;
		uint depth;

		uint handle;
		uint maxMipMapLevels;
		uint maxAnisotropy;

		TextureParameters params;
	};

}}


#endif //X808_GLTEXTURE2D_HPP
