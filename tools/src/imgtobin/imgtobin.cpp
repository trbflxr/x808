//
// Created by FLXR on 7/22/2018.
//

#include <cstdio>
#include <cstring>
#include <Freeimage/FreeImage.h>
#include <Freeimage/FreeImageUtilities.h>


int imgToBin(const char *in, const char *out, bool flipY, bool swapRB) {
	FREE_IMAGE_FORMAT fif;
	FIBITMAP *dib = nullptr;
	fif = FreeImage_GetFileType(in, 0);

	if (fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilename(in);
	}

	if (fif == FIF_UNKNOWN) {
		return 1;
	}

	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, in);
	}

	if (!dib) {
		fprintf(stderr, "Could not load image: %s\n", in);
		FreeImage_Unload(dib);

		return 1;
	}


	FIBITMAP *bitmap = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	unsigned char *pixels = FreeImage_GetBits(bitmap);
	unsigned w = FreeImage_GetWidth(bitmap);
	unsigned h = FreeImage_GetHeight(bitmap);
	unsigned b = FreeImage_GetBPP(bitmap);

	printf("width: %i, height %i, bits: %i\n", w, h, b);

	if (flipY) {
		FreeImage_FlipVertical(bitmap);
	}

	if (swapRB) {
		SwapRedBlue32(bitmap);
	}
	unsigned size = w * h * (b / 8);
	unsigned char *result = new unsigned char[size];

	memcpy(result, pixels, size);
	FreeImage_Unload(bitmap);

	FILE *res = fopen(out, "wb");

	int line = 0;
	for (size_t i = 0; i < size; ++i) {
		++line;
		fprintf(res, "0x%x, ", pixels[i]);
		if (line == 13) {
			fprintf(res, "\n");
			line = 0;
		}
	}

	fclose(res);

	return 0;
}

int main(int argc, char **argv) {
	FreeImage_Initialise();

	if (argc < 4) {
		printf("Syntax: %s [-flipy] <inputfile> <outputfile> <SwapRedBlue32(1-0)>\n", argv[0]);
		return 0;
	}

	bool flipY = false;

	int argn = 1;
	if (argv[argn][0] == '-') {
		if (strcmp(argv[argn], "-flipy") == 0) {
			++argn;
			flipY = true;
		} else {
			printf("Unknown argument: '%s'\n", argv[argn]);
			return 1;
		}
	}

	bool swapRB = static_cast<bool>(argv[argn + 2]);

	return imgToBin(argv[argn], argv[argn + 1], !flipY, swapRB);
}