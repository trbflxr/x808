//
// Created by FLXR on 6/30/2018.
//

#ifndef X808_TEXTURE2D_HPP
#define X808_TEXTURE2D_HPP


#include "texture.hpp"

namespace xe { namespace api {

	class XE_API Texture2D : public Texture {
	public:
		static Texture2D *create(uint width, uint height, TextureParameters params = { });

		static Texture2D *create(const std::string_view &name,
		                         const std::string_view &path,
		                         TextureParameters params = { },
		                         TextureLoadOptions options = { });


		virtual void setData(const void *pixels) = 0;

		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
	};

}}


#endif //X808_TEXTURE2D_HPP
