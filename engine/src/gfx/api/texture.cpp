//
// Created by FLXR on 6/30/2018.
//

#include "texture.hpp"

namespace xe { namespace gfx { namespace api {

	TextureWrap  Texture::wrapMode = TextureWrap::CLAMP;
	TextureFilter  Texture::filterMode = TextureFilter::LINEAR;

	byte Texture::getStrideFromFormat(TextureFormat format) {
		switch (format) {
			case TextureFormat::RGBA: return 4;
			case TextureFormat::RGB: return 3;
			case TextureFormat::LUMINANCE: return 4;
			case TextureFormat::LUMINANCE_ALPHA: return 1;
			default: return 0;
		}
	}

}}}