//
// Created by FLXR on 6/30/2018.
//



#include <xe/gfx/texture.hpp>
#include <xe/gfx/context.hpp>
#include <xe/math/math.hpp>
#include <xe/utils/log.hpp>

#include "platformtexture.hpp"
#include "opengl/gltexture.hpp"

namespace xe {

	Texture::Texture(uint width, uint height, uint depth, const TextureParameters &params) {
		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: {
				texture = new internal::GLTexture(width, height, depth, params);
				break;
			}

			default: {
				XE_FATAL("[Texture]: selected render API is not supported");
				texture = nullptr;
				break;
			}
		}
	}

	Texture::Texture(const string &name, const string &path,
	                 const TextureParameters &params,
	                 const TextureLoadOptions &options) {

		switch (Context::getRenderAPI()) {
			case RenderAPI::OPENGL: {
				texture = new internal::GLTexture(name, path, params, options);
				break;
			}

			default: {
				XE_FATAL("[Texture]: selected render API is not supported");
				texture = nullptr;
				break;
			}
		}
	}

	Texture::~Texture() {
		delete texture;
	}

	void Texture::bind(uint slot) const {
		texture->bind(slot);
	}

	void Texture::bindImageUnit(uint slot, uint index, TextureAccess access, uint level, uint layer) const {
		texture->bindImageUnit(slot, index, access, level, layer);
	}

	void Texture::unbind(uint slot) const {
		texture->unbind(slot);
	}

	void Texture::setData2D(const void *pixels) {
		texture->setData2D(pixels);
	}

	void Texture::generateMipMaps(const TextureTarget &target) {
		texture->generateMipMaps(target);
	}

	const string &Texture::getName() const {
		return texture->getName();
	}

	const string &Texture::getFilePath() const {
		return texture->getFilePath();
	}

	uint Texture::getWidth() const {
		return texture->getWidth();
	}

	uint Texture::getHeight() const {
		return texture->getHeight();
	}

	uint Texture::getDepth() const {
		return texture->getDepth();
	}

	uint Texture::getHandle() const {
		return texture->getHandle();
	}

	TextureTarget Texture::getTarget() const {
		return texture->getTarget();
	}

	uint Texture::getMaxMipMap(uint width, uint height) {
		uint max = __max(width, height);
		return static_cast<uint>(math::logf(max, 2.0f) - 1.0f);
	}

}