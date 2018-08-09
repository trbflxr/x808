//
// Created by FLXR on 8/9/2018.
//

#ifndef X808_ENUMS_HPP
#define X808_ENUMS_HPP


namespace xe {

	enum class TextureTarget {
		Tex1D,
		Tex2D,
		Tex3D,
		Tex2DArray,
		TexCubeMap,
		TexCubeMapArray
	};

	enum class TextureWrap {
		Repeat,
		Clamp,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum class TextureMinFilter {
		Nearest,
		Linear,
		NearestMipMapNearest,
		LinearMipMapNearest,
		NearestMipMapLinear,
		LinearMipMapLinear,
	};

	enum class TextureMagFilter {
		Nearest,
		Linear
	};

	enum class PixelType {
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Int,
		UnsignedInt,
		Float,
		HalfFloat
	};

	enum class PixelInternalFormat {
		DepthComponent,
		Alpha,
		Rgb,
		Rgba,
		Luminance,
		LuminanceAlpha,
		Rgb8,
		Rgb16,
		Rgba8,
		Rgba16,
		DepthComponent16,
		DepthComponent24,
		DepthComponent32,
		R32f,
		Rgba32f,
		Rgb32f,
		Rgba16f,
		Rgb16f
	};

	enum class PixelFormat {
		UnsignedShort,
		UnsignedInt,
		ColorIndex,
		StencilIndex,
		DepthComponent,
		Alpha,
		Rgb,
		Rgba,
		Luminance,
		LuminanceAlpha,
		Bgr,
		Bgra,
		Rg,
		DepthStencil
	};

	enum class TextureAccess {
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	enum class Attachment {
		Color0,
		Color1,
		Color2,
		Color3,
		Color4,
		Color5,
		Color6,
		Color7,
		Color8,
		Color9,
		Color10,
		Color11,
		Color12,
		Color13,
		Color14,
		Color15,
		Depth,
		Stencil
	};

}


#endif //X808_ENUMS_HPP
