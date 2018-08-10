//
// Created by FLXR on 8/9/2018.
//

#ifndef X808_GLENUMS_HPP
#define X808_GLENUMS_HPP

#include "gfx/api/enums.hpp"
#include "xeint.hpp"

namespace xe { namespace api {

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

}}

#endif //X808_GLENUMS_HPP
