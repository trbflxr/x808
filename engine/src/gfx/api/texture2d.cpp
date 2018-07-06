//
// Created by FLXR on 6/30/2018.
//

#include "texture2d.hpp"
#include "context.hpp"
#include "platform/opengl/gltexture2d.hpp"


xe::gfx::api::Texture2D *xe::gfx::api::Texture2D::create(uint width, uint height,
                                                         TextureParameters params,
                                                         TextureLoadOptions options) {
	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL : return new GLTexture2D(width, height, params, options);

		default: return nullptr;
	}
}

xe::gfx::api::Texture2D *xe::gfx::api::Texture2D::create(const std::string_view &name, const std::string_view &p,
                                                         TextureParameters params,
                                                         TextureLoadOptions options) {

	switch (Context::getRenderAPI()) {
		case RenderAPI::OPENGL : return new GLTexture2D(name, p, params, options);

		default: return nullptr;
	}
}




