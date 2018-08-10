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
			case PixelInternalFormat::Rg32f: return GL_RG32F;
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


	uint attachmentToGL(Attachment attachment) {
		switch (attachment) {
			case Attachment::Color0: return GL_COLOR_ATTACHMENT0;
			case Attachment::Color1: return GL_COLOR_ATTACHMENT1;
			case Attachment::Color2: return GL_COLOR_ATTACHMENT2;
			case Attachment::Color3: return GL_COLOR_ATTACHMENT3;
			case Attachment::Color4: return GL_COLOR_ATTACHMENT4;
			case Attachment::Color5: return GL_COLOR_ATTACHMENT5;
			case Attachment::Color6: return GL_COLOR_ATTACHMENT6;
			case Attachment::Color7: return GL_COLOR_ATTACHMENT7;
			case Attachment::Color8: return GL_COLOR_ATTACHMENT8;
			case Attachment::Color9: return GL_COLOR_ATTACHMENT9;
			case Attachment::Color10: return GL_COLOR_ATTACHMENT10;
			case Attachment::Color11: return GL_COLOR_ATTACHMENT11;
			case Attachment::Color12: return GL_COLOR_ATTACHMENT12;
			case Attachment::Color13: return GL_COLOR_ATTACHMENT13;
			case Attachment::Color14: return GL_COLOR_ATTACHMENT14;
			case Attachment::Color15: return GL_COLOR_ATTACHMENT15;
			case Attachment::Depth: return GL_DEPTH_ATTACHMENT;
			case Attachment::Stencil: return GL_STENCIL_ATTACHMENT;
		}
	}

	uint rendererBufferToGL(uint buffer) {
		uint result = 0;

		if (buffer & RendererBufferColor) {
			result |= GL_COLOR_BUFFER_BIT;
		}
		if (buffer & RendererBufferDepth) {
			result |= GL_DEPTH_BUFFER_BIT;
		}
		if (buffer & RendererBufferStencil) {
			result |= GL_STENCIL_BUFFER_BIT;
		}
		return result;
	}

	uint blendFunctionToGL(BlendFunction function) {
		switch (function) {
			case BlendFunction::Zero: return GL_ZERO;
			case BlendFunction::One: return GL_ONE;
			case BlendFunction::SourceAlpha: return GL_SRC_ALPHA;
			case BlendFunction::DestinationAlpha: return GL_DST_ALPHA;
			case BlendFunction::OneMinusSourceAlpha: return GL_ONE_MINUS_SRC_ALPHA;
		}
	}

	uint blendEquationToGL(BlendEquation equation){
		switch (equation){
			case BlendEquation::Add: return GL_ADD;
			case BlendEquation::Subtract: return GL_SUBTRACT;
		}
	}

	uint depthFunctionToGL(DepthFunction function) {
		switch (function) {
			case DepthFunction::Equal: return GL_EQUAL;
			case DepthFunction::Less: return GL_LESS;
		}
	}

	uint cullFaceToGL(CullFace cullFace) {
		switch (cullFace) {
			case CullFace::Front: return GL_FRONT;
			case CullFace::Back: return GL_BACK;
		}
	}

}}
