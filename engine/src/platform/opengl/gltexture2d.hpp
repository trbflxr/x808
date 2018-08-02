//
// Created by FLXR on 7/6/2018.
//

#ifndef X808_GLTEXTURE2D_HPP
#define X808_GLTEXTURE2D_HPP


#include "gfx/api/texture2d.hpp"

namespace xe { namespace gfx { namespace api {

	class GLTexture2D : public Texture2D {
	public:
		explicit GLTexture2D(uint width, uint height, TextureParameters params = { });

		explicit GLTexture2D(const std::string_view &name,
		                     const std::string_view &path,
		                     TextureParameters params = { },
		                     TextureLoadOptions options = { });

		~GLTexture2D() override;

		void bind(uint slot) const override;
		void unbind(uint slot) const override;

		inline const std::string &getName() const override { return name; }
		inline const std::string &getFilePath() const override { return fileName; }

		void setData(const void *pixels) override;

		inline uint getWidth() const override { return width; }
		inline uint getHeight() const override { return height; }

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

}}}


#endif //X808_GLTEXTURE2D_HPP
