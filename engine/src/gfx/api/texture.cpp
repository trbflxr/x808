//
// Created by FLXR on 6/30/2018.
//

#include "texture.hpp"
#include "context.hpp"
#include "math/math.hpp"
#include "platform/opengl/gltexture.hpp"

namespace xe { namespace api {


	Texture::Texture(const std::string_view &name,
	                 const std::string_view &path,
	                 uint width, uint height, uint depth,
	                 const TextureParameters &params) :
			name(name),
			fileName(path),
			width(width),
			height(height),
			depth(depth),
			params(params),
			maxMipMapLevels(0),
			maxAnisotropy(0) { }

	Texture *Texture::create(uint width, uint height, uint depth, const TextureParameters &params) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture(width, height, depth, params);

			default: return nullptr;
		}
	}

	Texture *Texture::create(const std::string_view &name,
	                         const std::string_view &path,
	                         const TextureParameters &params,
	                         const TextureLoadOptions &options) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL : return new GLTexture(name, path, params, options);

			default: return nullptr;
		}
	}

	uint Texture::getMaxMipMap(uint width, uint height) {
		uint max = __max(width, height);
		return static_cast<uint>(math::logf(max, 2.0f) - 1.0f);
	}

}}