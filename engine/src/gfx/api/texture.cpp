//
// Created by FLXR on 6/30/2018.
//

#include "texture.hpp"

xe::gfx::api::TextureWrap  xe::gfx::api::Texture::wrapMode = xe::gfx::api::TextureWrap::CLAMP;
xe::gfx::api::TextureFilter  xe::gfx::api::Texture::filterMode = xe::gfx::api::TextureFilter::LINEAR;

byte xe::gfx::api::Texture::getStrideFromFormat(xe::gfx::api::TextureFormat format) {
	switch (format) {
		case TextureFormat::RGB: return 3;
		case TextureFormat::RGBA: return 4;
		case TextureFormat::LUMINANCE_ALPHA: return 4;
		default: return 0;
	}
}
