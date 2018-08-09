//
// Created by FLXR on 8/9/2018.
//

#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe { namespace api {

	uint textureTargetToGL(TextureTarget target) {
		switch (target) {
			case TextureTarget::Tex1D: return GL_TEXTURE_1D;
			case TextureTarget::Tex2D: return GL_TEXTURE_2D;
			case TextureTarget::Tex3D: return GL_TEXTURE_3D;
			case TextureTarget::Tex2DArray: return GL_TEXTURE_2D_ARRAY;
			case TextureTarget::TexCubeMap: return GL_TEXTURE_CUBE_MAP;
			case TextureTarget::TexCubeMapArray: return GL_TEXTURE_CUBE_MAP_ARRAY;
		}
	}

	uint textureWrapToGL(TextureWrap wrap) {
		switch (wrap) {
			case TextureWrap::Repeat: return GL_REPEAT;
			case TextureWrap::Clamp: return GL_CLAMP;
			case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
			case TextureWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
			case TextureWrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
		}
	}

	uint textureMinFilterToGL(TextureMinFilter filter) {
		switch (filter) {
			case TextureMinFilter::Nearest: return GL_NEAREST;
			case TextureMinFilter::Linear: return GL_LINEAR;
			case TextureMinFilter::NearestMipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
			case TextureMinFilter::LinearMipMapNearest: return GL_LINEAR_MIPMAP_NEAREST;
			case TextureMinFilter::NearestMipMapLinear: return GL_NEAREST_MIPMAP_LINEAR;
			case TextureMinFilter::LinearMipMapLinear: return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	uint textureMagFilterToGL(TextureMagFilter filter) {
		switch (filter) {
			case TextureMagFilter::Nearest: return GL_NEAREST;
			case TextureMagFilter::Linear: return GL_LINEAR;
		}
	}

	uint pixelTypeToGL(PixelType type) {
		switch (type) {
			case PixelType::Byte: return GL_BYTE;
			case PixelType::UnsignedByte: return GL_UNSIGNED_BYTE;
			case PixelType::Short: return GL_SHORT;
			case PixelType::UnsignedShort: return GL_UNSIGNED_SHORT;
			case PixelType::Int: return GL_INT;
			case PixelType::UnsignedInt: return GL_UNSIGNED_INT;
			case PixelType::Float: return GL_FLOAT;
			case PixelType::HalfFloat: return GL_HALF_FLOAT;
		}
	}

	uint pixelInternalFormatToGL(PixelInternalFormat type) {
		switch (type) {
			case PixelInternalFormat::DepthComponent: return GL_DEPTH_COMPONENT;
			case PixelInternalFormat::Alpha: return GL_ALPHA;
			case PixelInternalFormat::Rgb: return GL_RGB;
			case PixelInternalFormat::Rgba: return GL_RGBA;
			case PixelInternalFormat::Luminance: return GL_LUMINANCE;
			case PixelInternalFormat::LuminanceAlpha: return GL_LUMINANCE_ALPHA;
			case PixelInternalFormat::Rgb8: return GL_RGB8;
			case PixelInternalFormat::Rgb16: return GL_RGB16;
			case PixelInternalFormat::Rgba8: return GL_RGBA8;
			case PixelInternalFormat::Rgba16: return GL_RGBA16;
			case PixelInternalFormat::DepthComponent16: return GL_DEPTH_COMPONENT16;
			case PixelInternalFormat::DepthComponent24: return GL_DEPTH_COMPONENT24;
			case PixelInternalFormat::DepthComponent32: return GL_DEPTH_COMPONENT32;
			case PixelInternalFormat::R32f: return GL_R32F;
			case PixelInternalFormat::Rgba32f: return GL_RGBA32F;
			case PixelInternalFormat::Rgb32f: return GL_RGB32F;
			case PixelInternalFormat::Rgba16f: return GL_RGBA16F;
			case PixelInternalFormat::Rgb16f: return GL_RGB16F;
		}
	}

	uint pixelFormatToGL(PixelFormat format) {
		switch (format) {
			case PixelFormat::UnsignedShort: return GL_UNSIGNED_SHORT;
			case PixelFormat::UnsignedInt: return GL_UNSIGNED_INT;
			case PixelFormat::ColorIndex: return GL_COLOR_INDEX;
			case PixelFormat::StencilIndex: return GL_STENCIL_INDEX;
			case PixelFormat::DepthComponent: return GL_DEPTH_COMPONENT;
			case PixelFormat::Alpha: return GL_ALPHA;
			case PixelFormat::Rgb: return GL_RGB;
			case PixelFormat::Rgba: return GL_RGBA;
			case PixelFormat::Luminance: return GL_LUMINANCE;
			case PixelFormat::LuminanceAlpha: return GL_LUMINANCE_ALPHA;
			case PixelFormat::Bgr: return GL_BGR;
			case PixelFormat::Bgra: return GL_BGRA;
			case PixelFormat::Rg: return GL_RG;
			case PixelFormat::DepthStencil: return GL_DEPTH_STENCIL;
		}
	}

	uint textureAccessToGL(TextureAccess textureAccess) {
		switch (textureAccess) {
			case TextureAccess::ReadOnly: return GL_READ_ONLY;
			case TextureAccess::WriteOnly: return GL_WRITE_ONLY;
			case TextureAccess::ReadWrite: return GL_READ_WRITE;
		}
	}

}}
