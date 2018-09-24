//
// Created by FLXR on 7/22/2018.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <codecvt>
#include <locale>
#include <cstdio>
#include <cstring>


int imgToBin(const wchar_t *in, const wchar_t *out) {
	int w;
	int h;
	int bpp;

	//in
	FILE *file = _wfopen(in, L"rb");
	if (!file) {
		fclose(file);
		fwprintf(stderr, L"Could not load image: %ls\n", in);
		return 1;
	}

	unsigned char *data = stbi_load_from_file(file, &w, &h, &bpp, 0);

	//get size
	long size = w * h * bpp;

	fclose(file);

	wprintf(L"width: %i, height %i, bits: %i\n", w, h, bpp * 8);
	wprintf(L"file size: %li\n", size);

	//out
	FILE *res = _wfopen(out, L"wb");

	int line = 0;
	for (size_t i = 0; i < size; ++i) {
		++line;
		fprintf(res, "%u,", data[i]);
		if (line == 13) {
			fprintf(res, "\n");
			line = 0;
		}
	}

	fclose(res);

	delete[] data;

	return 0;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Syntax: %s<inputfile> <outputfile>\n", argv[0]);
		return 0;
	}

	int argn = 1;
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return imgToBin(converter.from_bytes(argv[argn]).c_str(),
	                converter.from_bytes(argv[argn + 1]).c_str());
}