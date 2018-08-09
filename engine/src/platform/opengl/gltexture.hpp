//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLTEXTURE2D_HPP
#define X808_GLTEXTURE2D_HPP


#include "gfx/api/texture.hpp"

namespace xe { namespace api {

	class GLTexture : public Texture {
	public:
		explicit GLTexture(uint width, uint height, uint depth, const TextureParameters &params);

		explicit GLTexture(const std::string_view &name,
		                   const std::string_view &path,
		                   const TextureParameters &params,
		                   const TextureLoadOptions &options);

		~GLTexture() override;

		void bind(uint slot) const override;
		void bindImageUnit(uint slot, uint index, TextureAccess access, uint level, uint layer) const override;
		void unbind(uint slot) const override;

		void setData2D(const void *pixels) override;

		void generateMipMaps(const TextureTarget &target) override;

	private:
		uint loadInternal(const TextureLoadOptions *options);

		byte *loadFromFile(bool &fail, const TextureLoadOptions *options);

		void setTextureParams(const TextureTarget &target);
	};

}}


#endif //X808_GLTEXTURE2D_HPP
