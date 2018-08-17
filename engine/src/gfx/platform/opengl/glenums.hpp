//
// Created by FLXR on 8/9/2018.
//

#ifndef X808_GLENUMS_HPP
#define X808_GLENUMS_HPP

#include <xe/gfx/enums.hpp>
#include <xe/xeint.hpp>

namespace xe { namespace internal {

	uint textureTargetToGL(TextureTarget target);
	uint textureWrapToGL(TextureWrap wrap);
	uint textureMinFilterToGL(TextureMinFilter filter);
	uint textureMagFilterToGL(TextureMagFilter filter);
	uint pixelTypeToGL(PixelType type);
	uint pixelInternalFormatToGL(PixelInternalFormat type);
	uint pixelFormatToGL(PixelFormat format);
	uint textureAccessToGL(TextureAccess textureAccess);
	uint attachmentToGL(Attachment attachment);

	uint rendererBufferToGL(uint buffer);
	uint blendFunctionToGL(BlendFunction function);
	uint blendEquationToGL(BlendEquation equation);
	uint depthFunctionToGL(DepthFunction function);
	uint cullFaceToGL(CullFace cullFace);

	uint shaderTypeToGL(ShaderType type);

	uint beginModeToGL(BeginMode mode);

	uint bufferUsageToGL(BufferUsage usage);
	uint bufferStorageToGL(BufferStorage storage);

	uint materialFaceToGL(MaterialFace face);
	uint polygonModeToGL(PolygonMode mode);

}}

#endif //X808_GLENUMS_HPP
