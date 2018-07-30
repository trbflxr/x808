//
// Created by FLXR on 6/30/2018.
//

#include "texture2d.hpp"
#include "context.hpp"
#include "platform/opengl/gltexture2d.hpp"

namespace xe { namespace gfx { namespace api {

	Texture2D *Texture2D::create(uint width, uint height, TextureParameters params, bool mipMaps) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture2D(width, height, params, mipMaps);

			default: return nullptr;
		}
	}

	Texture2D *Texture2D::create(const std::string_view &name, const std::string_view &path,
	                             TextureParameters params,
	                             TextureLoadOptions options,
	                             bool mipMaps) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture2D(name, path, params, options, mipMaps);

			default: return nullptr;
		}
	}

}}}