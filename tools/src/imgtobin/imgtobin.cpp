//
// Created by FLXR on 7/22/2018.
//


#include <codecvt>
#include <locale>
#include <cstdio>
#include <cstring>
#include <Freeimage/FreeImage.h>
#include <Freeimage/FreeImageUtilities.h>


int imgToBin(const wchar_t *in, const wchar_t *out, bool flipY) {
	FREE_IMAGE_FORMAT fif;
	FIBITMAP *dib = nullptr;
	fif = FreeImage_GetFileTypeU(in, 0);

	if (fif == FIF_UNKNOWN) {
		fif = FreeImage_GetFIFFromFilenameU(in);
	}

	if (fif == FIF_UNKNOWN) {
		return 1;
	}

	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_LoadU(fif, in);
	}

	if (!dib) {
		fwprintf(stderr, L"Could not load image: %ls\n", in);
		FreeImage_Unload(dib);

		return 1;
	}


	FIBITMAP *bitmap = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	unsigned char *pixels = FreeImage_GetBits(bitmap);
	unsigned w = FreeImage_GetWidth(bitmap);
	unsigned h = FreeImage_GetHeight(bitmap);
	unsigned b = FreeImage_GetBPP(bitmap);

	wprintf(L"width: %i, height %i, bits: %i\n", w, h, b);

	if (flipY) {
		FreeImage_FlipVertical(bitmap);
	}

	if (FreeImage_GetRedMask(bitmap) == 0xff0000) {
		SwapRedBlue32(bitmap);
	}
	size_t size = w * h * (b / 8);
	unsigned char *result = new unsigned char[size];

	wprintf(L"file size: %llu\n", size);

	memcpy(result, pixels, size);
	FreeImage_Unload(bitmap);

	FILE *res = _wfopen(out, L"wb");
	
	int line = 0;
	for (size_t i = 0; i < size; ++i) {
		++line;
		fprintf(res, "%u, ", result[i]);
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

	if (argc < 3) {
		printf("Syntax: %s [-flipy] <inputfile> <outputfile>\n", argv[0]);
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

	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return imgToBin(converter.from_bytes(argv[argn]).c_str(),
	                converter.from_bytes(argv[argn + 1]).c_str(),
	                !flipY);
}