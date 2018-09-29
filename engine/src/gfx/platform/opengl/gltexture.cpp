//
// Created by FLXR on 7/6/2018.
//


#include <xe/utils/log.hpp>
#include <xe/loaders/imageloader.hpp>
#include "embedded/embedded.hpp"
#include "gltexture.hpp"
#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe { namespace internal {

	GLTexture::GLTexture(const string &name, uint width, uint height, uint depth, const TextureParameters &params) :
			name(name),
			path(L"NULL"),
			width(width),
			height(height),
			depth(params.target == TextureTarget::TexCubeMap ? 6 : depth),
			params(params) {

		handle = load(false);
	}

	GLTexture::GLTexture(const string &name, const wstring &path, const TextureParameters &params) :
			name(name),
			path(path),
			width(0),
			height(0),
			depth(1),
			params(params) {

		handle = load(true);
	}

	GLTexture::~GLTexture() {
		glCall(glDeleteTextures(1, &handle));
	}

	void GLTexture::bind(uint slot) const {
		uint target = textureTargetToGL(params.target);

		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(target, handle));
	}

	void GLTexture::bindImageUnit(uint index, TextureAccess access, uint level, uint layer) const {
		byte layered;
		switch (params.target) {
			case TextureTarget::Tex3D:
			case TextureTarget::Tex2DArray:
			case TextureTarget::TexCubeMap:
			case TextureTarget::TexCubeMapArray: layered = 1;
				break;
			case TextureTarget::Tex1D:
			case TextureTarget::Tex2D: layered = 0;
				break;
		}

		uint pif = pixelInternalFormatToGL(params.internalFormat);

		glCall(glActiveTexture(GL_TEXTURE0 + index));
		glCall(glBindImageTexture(index, handle, level, layered, layer, textureAccessToGL(access), pif));
	}

	void GLTexture::unbind(uint slot) const {
		static uint target = textureTargetToGL(params.target);

		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(target, 0));
	}

	void GLTexture::setData2D(const void *pixels) const {
		if (params.format == PixelFormat::DepthComponent) {
			XE_ERROR("[GLTexture]: ", name, " 'SetData' is unavailable for depth texture!");
			return;
		}

		glCall(glBindTexture(GL_TEXTURE_2D, handle));
		glCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, pixelFormatToGL(params.format),
		                       GL_UNSIGNED_BYTE, pixels));
	}

	void GLTexture::generateMipMaps(const TextureTarget &target) {
		glCall(glGenerateMipmap(textureTargetToGL(target)));
	}

	void GLTexture::copyTo(const Texture *texture) const {
		glCall(glCopyImageSubData(handle, textureTargetToGL(params.target), 0, 0, 0, 0,
		                          texture->getHandle(), textureTargetToGL(texture->getTarget()), 0, 0, 0, 0,
		                          width, height, 1));
	}

	uint GLTexture::load(bool fromFile) {
		byte *pixels = nullptr;
		bool fail = false;

		if (fromFile) {
			pixels = loadFromFile(fail);
		}

		uint handle;
		glCall(glGenTextures(1, &handle));
		glCall(glBindTexture(textureTargetToGL(params.target), handle));

		uint pif = pixelInternalFormatToGL(params.internalFormat);
		uint pf = pixelFormatToGL(params.format);
		uint pt = pixelTypeToGL(params.pixelType);

		switch (params.target) {
			case TextureTarget::Tex1D: {
				glCall(glTexImage1D(GL_TEXTURE_1D, 0, pif, width, 0, pf, pt, pixels));
				break;
			}

			case TextureTarget::Tex2D: {
				glCall(glTexImage2D(GL_TEXTURE_2D, 0, pif, width, height, 0, pf, pt, pixels));
				break;
			}

			case TextureTarget::Tex3D: {
				glCall(glTexImage3D(GL_TEXTURE_3D, 0, pif, width, height, depth, 0, pf, pt, pixels));
				break;
			}

			case TextureTarget::Tex2DArray: {
				glCall(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, pif, width, height, depth, 0, pf, pt, pixels));
				break;
			}

			case TextureTarget::TexCubeMap: {
				for (uint i = 0; i < depth; ++i) {
					glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, pif, width, height, 0, pf, pt, pixels));
				}
				break;
			}

			case TextureTarget::TexCubeMapArray: {
				glCall(glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, params.mipMapLevels + 1,
				                      pif, width, height, depth * 6));
				break;
			}
		}
		setTextureParams(params.target);

		glCall(glBindTexture(textureTargetToGL(params.target), 0));

		if (!fail) delete[] pixels;

		return handle;
	}

	byte *GLTexture::loadFromFile(bool &fail) {
		byte *outPixels = nullptr;

		uint bits;
		outPixels = ImageLoader::load(path.c_str(), &width, &height, &bits);

		if (!outPixels) {
			fail = true;
			name = "default";
			path = L"NULL";
			width = internal::DEFAULT_TEXTURE_W;
			height = internal::DEFAULT_TEXTURE_H;

			outPixels = internal::DEFAULT_TEXTURE;
			params.format = PixelFormat::Rgb;
			params.internalFormat = PixelInternalFormat::Rgb;
		} else {
			if (bits != 24 && bits != 32) {
				XE_FATAL(L"[GLTexture]: ", name, L" Unsupported image bit-depth! ('", bits, L"')");
			}

			if (bits == 24) {
				params.internalFormat = PixelInternalFormat::Rgb;
				params.format = PixelFormat::Rgb;
			} else {
				params.internalFormat = PixelInternalFormat::Rgba;
				params.format = PixelFormat::Rgba;
			}
		}

		return outPixels;
	}

	void GLTexture::setTextureParams(const TextureTarget &target) {
		uint glTarget = textureTargetToGL(target);

		//filtering mode
		glCall(glTexParameterf(glTarget, GL_TEXTURE_MIN_FILTER, textureMinFilterToGL(params.minFilter)));
		glCall(glTexParameterf(glTarget, GL_TEXTURE_MAG_FILTER, textureMagFilterToGL(params.magFilter)));

		//wrap mode
		glCall(glTexParameterf(glTarget, GL_TEXTURE_WRAP_S, textureWrapToGL(params.wrap)));
		glCall(glTexParameterf(glTarget, GL_TEXTURE_WRAP_T, textureWrapToGL(params.wrap)));
		glCall(glTexParameterf(glTarget, GL_TEXTURE_WRAP_R, textureWrapToGL(params.wrap)));

		//gen mip maps
		if (params.mipMapLevels == MIP_MAP_AUTO) {
			maxMipMapLevels = Texture::getMaxMipMap(width, height);
			params.minFilter = TextureMinFilter::LinearMipMapLinear;
		} else if (params.mipMapLevels > 0) {
			maxMipMapLevels = __min(Texture::getMaxMipMap(width, height), params.mipMapLevels);
			params.minFilter = TextureMinFilter::LinearMipMapLinear;
		}

		//set mip maps
		if (maxMipMapLevels) {
			glCall(glTexParameterf(glTarget, GL_TEXTURE_BASE_LEVEL, 0));
			glCall(glTexParameterf(glTarget, GL_TEXTURE_MAX_LEVEL, maxMipMapLevels));
			generateMipMaps(target);
		}

		//get max anisotropic filtering
		static float aniso = 0.0f;
		if (aniso == 0.0f) {
			glCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso));
		}
		if (params.anisotropy == ANISOTROPY_AUTO) {
			maxAnisotropy = static_cast<uint>(aniso);
		} else if (params.anisotropy > 0) {
			maxAnisotropy = __min(static_cast<uint>(aniso), params.anisotropy);
		}

		//set anisotropic filtering
		if (params.anisotropy) {
			glCall(glTexParameterf(glTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy));
		}
	}

}}