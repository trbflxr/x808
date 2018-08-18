//
// Created by FLXR on 8/16/2018.
//

#include <FreeImage/FreeImage.h>
#include <FreeImage/FreeImageUtilities.h>
#include <xe/utils/log.hpp>
#include <xe/loaders/imageloader.hpp>

namespace xe {

	byte *ImageLoader::load(const char *path, uint *width, uint *height, uint *bits, bool flipY) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(path, 0);

		if (fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(path);
		}

		if (fif == FIF_UNKNOWN) {
			return nullptr;
		}

		if (FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_Load(fif, path);
		}

		if (!dib) {
			XE_ERROR("[LoadImage]: Could not load image: ", path);
			FreeImage_Unload(dib);

			return nullptr;
		}


		FIBITMAP *bitmap = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(dib);

		byte *pixels = FreeImage_GetBits(bitmap);
		uint w = FreeImage_GetWidth(bitmap);
		uint h = FreeImage_GetHeight(bitmap);
		uint b = FreeImage_GetBPP(bitmap);

		if (flipY) {
			FreeImage_FlipVertical(bitmap);
		}

		if (FreeImage_GetRedMask(bitmap) == 0xff0000) {
			SwapRedBlue32(bitmap);
		}

		if (width) *width = w;
		if (height) *height = h;
		if (bits) *bits = b;

		uint size = w * h * (b / 8);
		byte *result = new byte[size];

		memcpy(result, pixels, size);
		FreeImage_Unload(bitmap);

		return result;
	}

	byte *ImageLoader::load(const string &path, uint *width, uint *height, uint *bits, bool flipY) {
		return load(path.c_str(), width, height, bits, flipY);
	}

}