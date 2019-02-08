//
// Created by FLXR on 8/9/2018.
//

#include <GL/glew.h>
#include <xe/config.hpp>
#include "glcommon.hpp"
#include "glenums.hpp"

namespace xe { namespace internal {

	uint textureTargetToGL(TextureTarget target) noexcept {
		switch (target) {
			case TextureTarget::Tex1D: return GL_TEXTURE_1D;
			case TextureTarget::Tex2D: return GL_TEXTURE_2D;
			case TextureTarget::Tex3D: return GL_TEXTURE_3D;
			case TextureTarget::Tex2DArray: return GL_TEXTURE_2D_ARRAY;
			case TextureTarget::TexCubeMap: return GL_TEXTURE_CUBE_MAP;
			case TextureTarget::TexCubeMapArray: return GL_TEXTURE_CUBE_MAP_ARRAY;
		}
		return 0;
	}

	uint textureWrapToGL(TextureWrap wrap) noexcept {
		switch (wrap) {
			case TextureWrap::Repeat: return GL_REPEAT;
			case TextureWrap::Clamp: return GL_CLAMP;
			case TextureWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
			case TextureWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
			case TextureWrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
		}
		return 0;
	}

	uint textureMinFilterToGL(TextureMinFilter filter) noexcept {
		switch (filter) {
			case TextureMinFilter::Nearest: return GL_NEAREST;
			case TextureMinFilter::Linear: return GL_LINEAR;
			case TextureMinFilter::NearestMipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
			case TextureMinFilter::LinearMipMapNearest: return GL_LINEAR_MIPMAP_NEAREST;
			case TextureMinFilter::NearestMipMapLinear: return GL_NEAREST_MIPMAP_LINEAR;
			case TextureMinFilter::LinearMipMapLinear: return GL_LINEAR_MIPMAP_LINEAR;
		}
		return 0;
	}

	uint textureMagFilterToGL(TextureMagFilter filter) noexcept {
		switch (filter) {
			case TextureMagFilter::Nearest: return GL_NEAREST;
			case TextureMagFilter::Linear: return GL_LINEAR;
		}
		return 0;
	}

	uint pixelTypeToGL(PixelType type) noexcept {
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
		return 0;
	}

	uint pixelInternalFormatToGL(PixelInternalFormat type) noexcept {
		switch (type) {
			case PixelInternalFormat::DepthComponent: return GL_DEPTH_COMPONENT;
			case PixelInternalFormat::Alpha: return GL_ALPHA;
			case PixelInternalFormat::Rgb: return gConfig.useSRGB ? GL_SRGB : GL_RGB;
			case PixelInternalFormat::Rgba: return gConfig.useSRGB ? GL_SRGB_ALPHA : GL_RGBA;
			case PixelInternalFormat::Luminance: return GL_LUMINANCE;
			case PixelInternalFormat::LuminanceAlpha: return GL_LUMINANCE_ALPHA;
			case PixelInternalFormat::Rgb8: return GL_RGB8;
			case PixelInternalFormat::Rgb16: return GL_RGB16;
			case PixelInternalFormat::Rgba8: return GL_RGBA8;
			case PixelInternalFormat::Rgba16: return GL_RGBA16;
			case PixelInternalFormat::DepthComponent16: return GL_DEPTH_COMPONENT16;
			case PixelInternalFormat::DepthComponent24: return GL_DEPTH_COMPONENT24;
			case PixelInternalFormat::DepthComponent32: return GL_DEPTH_COMPONENT32;
			case PixelInternalFormat::Depth32fStencil8: return GL_DEPTH32F_STENCIL8;
			case PixelInternalFormat::DepthComponent32f: return GL_DEPTH_COMPONENT32F;
			case PixelInternalFormat::R16f: return GL_R16F;
			case PixelInternalFormat::R32f: return GL_R32F;
			case PixelInternalFormat::Rg16f: return GL_RG16F;
			case PixelInternalFormat::Rgba32f: return GL_RGBA32F;
			case PixelInternalFormat::Rgb32f: return GL_RGB32F;
			case PixelInternalFormat::Rgba16f: return GL_RGBA16F;
			case PixelInternalFormat::Rgb16f: return GL_RGB16F;
			case PixelInternalFormat::Rg32f: return GL_RG32F;
		}
		return 0;
	}

	uint pixelFormatToGL(PixelFormat format) noexcept {
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
			case PixelFormat::Red: return GL_RED;
			case PixelFormat::DepthStencil: return GL_DEPTH_STENCIL;
		}
		return 0;
	}

	uint textureAccessToGL(TextureAccess textureAccess) noexcept {
		switch (textureAccess) {
			case TextureAccess::ReadOnly: return GL_READ_ONLY;
			case TextureAccess::WriteOnly: return GL_WRITE_ONLY;
			case TextureAccess::ReadWrite: return GL_READ_WRITE;
		}
		return 0;
	}


	uint attachmentToGL(Attachment attachment) noexcept {
		switch (attachment) {
			case Attachment::None:return GL_NONE;
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
			case Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;
		}
		return 0;
	}

	uint rendererBufferToGL(uint buffer) noexcept {
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

	uint blendFunctionToGL(BlendFunction function) noexcept {
		switch (function) {
			case BlendFunction::Zero: return GL_ZERO;
			case BlendFunction::One: return GL_ONE;
			case BlendFunction::SourceAlpha: return GL_SRC_ALPHA;
			case BlendFunction::DestinationAlpha: return GL_DST_ALPHA;
			case BlendFunction::OneMinusSourceAlpha: return GL_ONE_MINUS_SRC_ALPHA;
		}
		return 0;
	}

	uint blendEquationToGL(BlendEquation equation) noexcept {
		switch (equation) {
			case BlendEquation::Add: return GL_FUNC_ADD;
			case BlendEquation::Subtract: return GL_FUNC_SUBTRACT;
		}
		return 0;
	}

	uint depthFunctionToGL(DepthFunction function) noexcept {
		switch (function) {
			case DepthFunction::Equal: return GL_EQUAL;
			case DepthFunction::Less: return GL_LESS;
		}
		return 0;
	}

	uint cullFaceToGL(CullFace cullFace) noexcept {
		switch (cullFace) {
			case CullFace::Front: return GL_FRONT;
			case CullFace::Back: return GL_BACK;
		}
		return 0;
	}

	uint shaderTypeToGL(ShaderType type) noexcept {
		switch (type) {
			case ShaderType::Vert: return GL_VERTEX_SHADER;
			case ShaderType::Frag: return GL_FRAGMENT_SHADER;
			case ShaderType::Geom: return GL_GEOMETRY_SHADER;
			case ShaderType::TessEval: return GL_TESS_EVALUATION_SHADER;
			case ShaderType::TessControl: return GL_TESS_CONTROL_SHADER;
			case ShaderType::Compute: return GL_COMPUTE_SHADER;
		}
		return 0;
	}

	uint beginModeToGL(BeginMode mode) noexcept {
		switch (mode) {
			case BeginMode::Points: return GL_POINTS;
			case BeginMode::Lines: return GL_LINES;
			case BeginMode::LineLoop: return GL_LINE_LOOP;
			case BeginMode::LineStrip: return GL_LINE_STRIP;
			case BeginMode::Triangles: return GL_TRIANGLES;
			case BeginMode::TriangleStrip: return GL_TRIANGLE_STRIP;
			case BeginMode::TriangleFan: return GL_TRIANGLE_FAN;
			case BeginMode::Quads: return GL_QUADS;
			case BeginMode::QuadStrip: return GL_QUAD_STRIP;
			case BeginMode::Polygon: return GL_POLYGON;
			case BeginMode::Patches: return GL_PATCHES;
		}
		return 0;
	}

	uint bufferUsageToGL(BufferUsage usage) noexcept {
		switch (usage) {
			case BufferUsage::StreamDraw: return GL_STREAM_DRAW;
			case BufferUsage::StreamRead: return GL_STREAM_READ;
			case BufferUsage::StreamCopy: return GL_STREAM_COPY;
			case BufferUsage::StaticDraw: return GL_STATIC_DRAW;
			case BufferUsage::StaticRead: return GL_STATIC_READ;
			case BufferUsage::StaticCopy: return GL_STATIC_COPY;
			case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
			case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
			case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		}
		return 0;
	}

	uint bufferStorageToGL(BufferStorage storage) noexcept {
		switch (storage) {
			case BufferStorage::MapRead: return GL_MAP_READ_BIT;
			case BufferStorage::MapWrite: return GL_MAP_WRITE_BIT;
			case BufferStorage::MapPersistent: return GL_MAP_PERSISTENT_BIT;
			case BufferStorage::MapCoherent: return GL_MAP_COHERENT_BIT;
			case BufferStorage::Dynamic: return GL_DYNAMIC_STORAGE_BIT;
			case BufferStorage::Client: return GL_CLIENT_STORAGE_BIT;
		}
		return 0;
	}

	uint materialFaceToGL(MaterialFace face) noexcept {
		switch (face) {
			case MaterialFace::Front: return GL_FRONT;
			case MaterialFace::Back: return GL_BACK;
			case MaterialFace::FrontAndBack: return GL_FRONT_AND_BACK;
		}
		return 0;
	}

	uint polygonModeToGL(PolygonMode mode) noexcept {
		switch (mode) {
			case PolygonMode::Point: return GL_POINT;
			case PolygonMode::Line: return GL_LINE;
			case PolygonMode::Fill: return GL_FILL;
		}
		return 0;
	}

	uint stencilOpToGL(StencilOp op) noexcept {
		switch (op) {
			case StencilOp::Zero: return GL_ZERO;
			case StencilOp::Invert: return GL_INVERT;
			case StencilOp::Keep: return GL_KEEP;
			case StencilOp::Replace: return GL_REPLACE;
			case StencilOp::Incr: return GL_INCR;
			case StencilOp::Decr: return GL_DECR;
			case StencilOp::IncrWrap: return GL_INCR_WRAP;
			case StencilOp::DecrWrap: return GL_DECR_WRAP;
		}
		return 0;
	}

	uint stencilFuncToGL(StencilFunction func) noexcept {
		switch (func) {
			case StencilFunction::Never: return GL_NEVER;
			case StencilFunction::Less: return GL_LESS;
			case StencilFunction::Equal: return GL_EQUAL;
			case StencilFunction::Lequal: return GL_LEQUAL;
			case StencilFunction::Greater: return GL_GREATER;
			case StencilFunction::Notequal: return GL_NOTEQUAL;
			case StencilFunction::Gequal: return GL_GEQUAL;
			case StencilFunction::Always: return GL_ALWAYS;
		}
		return 0;
	}

	uint stencilFaceToGL(StencilFace face) noexcept {
		switch (face) {
			case StencilFace::Front: return GL_FRONT;
			case StencilFace::Back: return GL_BACK;
			case StencilFace::FrontAndBack: return GL_FRONT_AND_BACK;
		}
		return 0;
	}

	uint memoryBarrierToGL(MemoryBarrier barrier) noexcept {
		switch (barrier) {
			case MemoryBarrier::ShaderImageAccess: return GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;
			case MemoryBarrier::ShaderStorage: return GL_SHADER_STORAGE_BARRIER_BIT;
			case MemoryBarrier::All: return GL_ALL_BARRIER_BITS;
		}
		return 0;
	}

}}
