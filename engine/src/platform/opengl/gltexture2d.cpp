//
// Created by FLXR on 7/6/2018.
//

#include "gltexture2d.hpp"
#include "glcommon.hpp"
#include "utils/loadimage.hpp"
#include "embedded/embedded.hpp"

namespace xe { namespace gfx { namespace api {

	uint textureFormatToGL(TextureFormat format) {
		switch (format) {
			case TextureFormat::RGBA: return GL_RGBA;
			case TextureFormat::RGB: return GL_RGB;
			case TextureFormat::LUMINANCE: return GL_LUMINANCE;
			case TextureFormat::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
			default: return 0;
		}
	}

	uint textureWrapToGL(TextureWrap wrap) {
		switch (wrap) {
			case TextureWrap::CLAMP: return GL_CLAMP;
			case TextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
			case TextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
			case TextureWrap::REPEAT: return GL_REPEAT;
			case TextureWrap::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
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
		if (parameters.format == TextureFormat::DEPTH) {
			XE_ERROR("[GLTexture2D]: 'SetData' is unavailable for depth texture!");
			return;
		}

		glCall(glBindTexture(GL_TEXTURE_2D, handle));
		glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
		                       textureFormatToGL(parameters.format), GL_UNSIGNED_BYTE, pixels));
	}

	uint GLTexture2D::load() {
		// todo: split  into loading from file and generating from data
		byte *pixels = nullptr;

		bool fail = false;

		if (fileName != "NULL") {
			uint bits;
			// FreeImage loads bottom->top
			pixels = utils::loadImage(fileName.data(), &width, &height, &bits, !loadOptions.flipY);

			if (!pixels) {
				fail = true;
				fileName = "default";
				width = internal::DEFAULT_TEXTURE_W;
				height = internal::DEFAULT_TEXTURE_H;

				pixels = internal::DEFAULT_TEXTURE;
				parameters.format = TextureFormat::RGBA;
			} else {
				if (bits != 24 && bits != 32) {
					XE_FATAL("[Texture] Unsupported image bit-depth! ('", bits, "')");
				}
				parameters.format = bits == 24 ? TextureFormat::RGB : TextureFormat::RGBA;
			}

		}

		uint handle;
		glCall(glGenTextures(1, &handle));
		glCall(glBindTexture(GL_TEXTURE_2D, handle));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		                       parameters.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR
		                                                                  : GL_NEAREST));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		                       parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToGL(wrapMode)));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToGL(wrapMode)));

		if (parameters.format == TextureFormat::DEPTH) {
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0,
			                    GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, nullptr));

			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE));
		} else {
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, textureFormatToGL(parameters.format), width, height, 0,
			                    textureFormatToGL(parameters.format),
			                    GL_UNSIGNED_BYTE, pixels ? pixels : nullptr));

			glCall(glGenerateMipmap(GL_TEXTURE_2D));
		}

		glCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (!fail) {
			delete[] pixels;
		}

		return handle;
	}

}}}