//
// Created by FLXR on 6/30/2018.
//

#include "texture.hpp"
#include "context.hpp"
#include "platform/opengl/gltexture.hpp"

namespace xe { namespace api {

	TextureWrap  Texture::wrapMode = TextureWrap::CLAMP;
	TextureFilter  Texture::filterMode = TextureFilter::TRILINEAR;

	Texture::Texture(TextureTarget target) :
			target(target) { }

	byte Texture::getStrideFromFormat(TextureFormat format) {
		switch (format) {
			case TextureFormat::RGBA: return 4;
			case TextureFormat::RGB: return 3;
			case TextureFormat::LUMINANCE: return 4;
			case TextureFormat::LUMINANCE_ALPHA: return 1;
			default: return 0;
		}
	}

	Texture *Texture::create(uint width, uint height, TextureParameters params) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture(width, height, params);

			default: return nullptr;
		}
	}

	Texture *Texture::create(const std::string_view &name, const std::string_view &path,
	                         TextureParameters params,
	                         TextureLoadOptions options) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture(name, path, params, options);

			default: return nullptr;
		}
	}

}}