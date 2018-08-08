//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLTEXTURE2D_HPP
#define X808_GLTEXTURE2D_HPP


#include "gfx/api/texture.hpp"

namespace xe { namespace api {

	class GLTexture : public Texture {
	public:
		explicit GLTexture(uint width, uint height, TextureParameters params);

		explicit GLTexture(const std::string_view &name,
		                     const std::string_view &path,
		                     TextureParameters params,
		                     TextureLoadOptions options);

		~GLTexture() override;

		void bind(uint slot) const override;
		void unbind(uint slot) const override;

		inline const std::string &getName() const override { return name; }
		inline const std::string &getFilePath() const override { return fileName; }

		void setData(const void *pixels) override;

		inline uint getWidth() const override { return width; }
		inline uint getHeight() const override { return height; }

		uint getDepth() const override { return 1; }

		inline uint getHandle() const override { return handle; }

	private:
		uint load();

		byte *loadFromFile(bool &fail);

	private:
		std::string name;
		std::string fileName;

		uint handle;
		uint width;
		uint height;

		TextureParameters parameters;
		TextureLoadOptions loadOptions;
	};

}}


#endif //X808_GLTEXTURE2D_HPP
