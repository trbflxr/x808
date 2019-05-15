//
// Created by FLXR on 8/9/2018.
//

#ifndef X808_GLENUMS_HPP
#define X808_GLENUMS_HPP

#include <xe/gfx/enums.hpp>
#include <xe/xeint.hpp>

namespace xe::internal {

  uint textureTargetToGL(TextureTarget target) noexcept;
  uint textureWrapToGL(TextureWrap wrap) noexcept;
  uint textureMinFilterToGL(TextureMinFilter filter) noexcept;
  uint textureMagFilterToGL(TextureMagFilter filter) noexcept;
  uint pixelTypeToGL(PixelType type) noexcept;
  uint pixelInternalFormatToGL(PixelInternalFormat type) noexcept;
  uint pixelFormatToGL(PixelFormat format) noexcept;
  uint textureAccessToGL(TextureAccess textureAccess) noexcept;
  uint attachmentToGL(Attachment attachment) noexcept;

  uint rendererBufferToGL(uint buffer) noexcept;
  uint blendFunctionToGL(BlendFunction function) noexcept;
  uint blendEquationToGL(BlendEquation equation) noexcept;
  uint depthFunctionToGL(DepthFunction function) noexcept;
  uint cullFaceToGL(CullFace cullFace) noexcept;

  uint shaderTypeToGL(ShaderType type) noexcept;

  uint beginModeToGL(BeginMode mode) noexcept;

  uint bufferUsageToGL(BufferUsage usage) noexcept;
  uint bufferStorageToGL(BufferStorage storage) noexcept;

  uint materialFaceToGL(MaterialFace face) noexcept;
  uint polygonModeToGL(PolygonMode mode) noexcept;

  uint stencilOpToGL(StencilOp op) noexcept;
  uint stencilFuncToGL(StencilFunction func) noexcept;
  uint stencilFaceToGL(StencilFace face) noexcept;

  uint memoryBarrierToGL(MemoryBarrier barrier) noexcept;

}

#endif //X808_GLENUMS_HPP
