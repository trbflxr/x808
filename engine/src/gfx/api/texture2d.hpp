//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE2D_HPP
#define X808_TEXTURE2D_HPP


#include "texture.hpp"

namespace xe { namespace gfx { namespace api {

	class XE_API Texture2D : public Texture {
	public:
		explicit Texture2D(uint width, uint height,
		                   TextureParameters params = { },
		                   TextureLoadOptions options = { });

		explicit Texture2D(uint width, uint height, uint color,
		                   TextureParameters params = { },
		                   TextureLoadOptions options = { });

		explicit Texture2D(const std::string_view &name,
		                   const std::string_view &path,
		                   TextureParameters params = { },
		                   TextureLoadOptions options = { });

		~Texture2D() override;

		void bind(uint slot) const override;
		void unbind(uint slot) const override;

		inline std::string_view getName() const override { return name; }
		inline std::string_view getFilePath() const override { return fileName; }

		void setData(const void *pixels);
		void setData(uint color);

		inline uint getWidth() const { return width; }
		inline uint getHeight() const { return height; }

		inline uint getHandle() const override { return handle; }

		static uint textureFormatToGL(TextureFormat format);
		static uint textureWrapToGL(TextureWrap wrap);

	private:
		uint load();

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


#endif //X808_TEXTURE2D_HPP
