//
// Created by FLXR on 7/6/2018.
//

#include "gltexture2d.hpp"
#include "glcommon.hpp"
#include "utils/loadimage.hpp"
#include "embedded/embedded.hpp"

namespace xe { namespace gfx { namespace api {

	uint textureInternalFormatToGL(TextureFormat format) {
		switch (format) {
			case TextureFormat::RGBA: return GL_RGBA;
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::LUMINANCE: return GL_LUMINANCE;
			case TextureFormat::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
			case TextureFormat::DEPTH16: return GL_DEPTH_COMPONENT16;
			case TextureFormat::DEPTH24: return GL_DEPTH_COMPONENT24;
			case TextureFormat::RG32F: return GL_RG32F;
		}
	}

	uint textureFormatToGL(TextureFormat format) {
		switch (format) {
			case TextureFormat::RGBA: return GL_RGBA;
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::LUMINANCE: return GL_LUMINANCE;
			case TextureFormat::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
			case TextureFormat::DEPTH16: return GL_DEPTH_COMPONENT;
			case TextureFormat::DEPTH24: return GL_DEPTH_COMPONENT;
			case TextureFormat::RG32F: return GL_RGBA;
		}
	}

	uint textureWrapToGL(TextureWrap wrap) {
		switch (wrap) {
			case TextureWrap::CLAMP: return GL_CLAMP;
			case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
			case TextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
			case TextureWrap::REPEAT: return GL_REPEAT;
			case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
		}
	}

	uint textureFilterToGL(TextureFilter filter) {
		switch (filter) {
			case TextureFilter::NEAREST: return GL_NEAREST;
			case TextureFilter::BILINEAR: return GL_LINEAR;
			default: return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	uint textureFilterAnisotropyToGL(TextureFilter filter) {
		switch (filter) {
			case TextureFilter::AF2: return 2;
			case TextureFilter::AF4: return 4;
			case TextureFilter::AF8: return 8;
			case TextureFilter::AF16: return 16;
			default: return 0;
		}
	}

	GLTexture2D::GLTexture2D(uint width, uint height, TextureParameters params) :
			fileName("NULL"),
			width(width),
			height(height),
			parameters(params) {

		handle = load();
	}

	GLTexture2D::GLTexture2D(const std::string_view &name, const std::string_view &path,
	                         TextureParameters params,
	                         TextureLoadOptions options) :
			name(name),
			fileName(path),
			parameters(params),
			loadOptions(options) {

		handle = load();
	}

	GLTexture2D::~GLTexture2D() {
		glCall(glDeleteTextures(1, &handle));
	}

	void GLTexture2D::bind(uint slot) const {
		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(GL_TEXTURE_2D, handle));
	}

	void GLTexture2D::unbind(uint slot) const {
		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void GLTexture2D::setData(const void *pixels) {
		if (parameters.format == TextureFormat::DEPTH24) {
			XE_ERROR("[GLTexture2D]: 'SetData' is unavailable for depth texture!");
			return;
		}

		glCall(glBindTexture(GL_TEXTURE_2D, handle));
		glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
		                       textureInternalFormatToGL(parameters.format), GL_UNSIGNED_BYTE, pixels));
	}

	uint GLTexture2D::load() {
		byte *pixels = nullptr;
		bool fail = false;

		if (fileName != "NULL") {
			pixels = loadFromFile(fail);
		}

		uint handle;
		glCall(glGenTextures(1, &handle));
		glCall(glBindTexture(GL_TEXTURE_2D, handle));

		//filtering mode
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToGL(parameters.filter)));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		                       parameters.filter == TextureFilter::NEAREST ? GL_NEAREST : GL_LINEAR));

		//wrap mode
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToGL(wrapMode)));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToGL(wrapMode)));

		//set data
		glCall(glTexImage2D(GL_TEXTURE_2D, 0, textureInternalFormatToGL(parameters.format), width, height, 0,
		                    textureFormatToGL(parameters.format), GL_UNSIGNED_BYTE, pixels));

		//anisotropic filtering setup
		if (parameters.filter != TextureFilter::NEAREST && parameters.filter != TextureFilter::BILINEAR) {
			glCall(glGenerateMipmap(GL_TEXTURE_2D));

			uint anisotropy = textureFilterAnisotropyToGL(parameters.filter);
			if (anisotropy) {
				glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy));
			}

		} else {
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
		}


		glCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (!fail) delete[] pixels;

		return handle;
	}

	byte *GLTexture2D::loadFromFile(bool &fail) {
		byte *outPixels = nullptr;

		uint bits;
		// FreeImage loads bottom->top
		outPixels = utils::loadImage(fileName.data(), &width, &height, &bits, !loadOptions.flipY);

		if (!outPixels) {
			fail = true;
			fileName = "default";
			width = internal::DEFAULT_TEXTURE_W;
			height = internal::DEFAULT_TEXTURE_H;

			outPixels = internal::DEFAULT_TEXTURE;
			parameters.format = TextureFormat::RGBA;
		} else {
			if (bits != 24 && bits != 32) {
				XE_FATAL("[Texture] Unsupported image bit-depth! ('", bits, "')");
			}
			parameters.format = bits == 24 ? TextureFormat::RGB : TextureFormat::RGBA;
		}

		return outPixels;
	}

}}}