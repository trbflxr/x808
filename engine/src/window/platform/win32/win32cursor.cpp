//
// Created by FLXR on 7/15/2018.
//

#undef NOGDI
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#define NOGDI

#include <xe/window/cursor.hpp>
#include <xe/utils/logger.hpp>
#include <xe/utils/assert.hpp>

namespace xe {

	Cursor::Cursor(const byte *pixels, vec2 size, vec2 hotspot) :
			cursor(nullptr) {

		release();

		BITMAPV5HEADER bitmapHeader;
		memset(&bitmapHeader, 0, sizeof(BITMAPV5HEADER));

		bitmapHeader.bV5Size = sizeof(BITMAPV5HEADER);
		bitmapHeader.bV5Width = static_cast<LONG>(size.x);
		bitmapHeader.bV5Height = -static_cast<LONG>(size.y);
		bitmapHeader.bV5Planes = 1;
		bitmapHeader.bV5BitCount = 32;
		bitmapHeader.bV5Compression = BI_BITFIELDS;
		bitmapHeader.bV5RedMask = 0x00ff0000;
		bitmapHeader.bV5GreenMask = 0x0000ff00;
		bitmapHeader.bV5BlueMask = 0x000000ff;
		bitmapHeader.bV5AlphaMask = 0xff000000;

		byte *bitmapData = nullptr;

		HDC screenDC = GetDC(nullptr);
		HBITMAP color = CreateDIBSection(
				screenDC,
				reinterpret_cast<const BITMAPINFO *>(&bitmapHeader),
				DIB_RGB_COLORS,
				reinterpret_cast<void **>(&bitmapData),
				nullptr,
				0
		);
		ReleaseDC(nullptr, screenDC);

		if (!color) {
			XE_CORE_ERROR("[Win32Cursor]: Failed to create cursor color bitmap");
			XE_ASSERT(color);
		}

		memcpy(bitmapData, pixels, static_cast<size_t >(size.x * size.y * 4));

		HBITMAP mask = CreateBitmap(static_cast<int32>(size.x), static_cast<int32>(size.y), 1, 1, nullptr);

		if (!mask) {
			DeleteObject(color);
			XE_CORE_ERROR("[Win32Cursor]: Failed to create cursor mask bitmap");
			XE_ASSERT(mask);
		}

		ICONINFO cursorInfo;
		memset(&cursorInfo, 0, sizeof(ICONINFO));

		cursorInfo.fIcon = FALSE;
		cursorInfo.xHotspot = hotspot.x;
		cursorInfo.yHotspot = hotspot.y;
		cursorInfo.hbmColor = color;
		cursorInfo.hbmMask = mask;

		cursor = reinterpret_cast<HCURSOR>(CreateIconIndirect(&cursorInfo));

		DeleteObject(color);
		DeleteObject(mask);

		if (!cursor) {
			XE_CORE_ERROR("[Win32Cursor]: Failed to create cursor from bitmaps");
			XE_ASSERT(cursor);
		}
	}

	Cursor::Cursor(Cursor::Type type) :
			cursor(nullptr) {

		release();

		LPCTSTR shape{ };
		switch (type) {
			case Cursor::Arrow: shape = IDC_ARROW;
				break;
			case Cursor::ArrowWait: shape = IDC_APPSTARTING;
				break;
			case Cursor::Wait: shape = IDC_WAIT;
				break;
			case Cursor::Text: shape = IDC_IBEAM;
				break;
			case Cursor::Hand: shape = IDC_HAND;
				break;
			case Cursor::SizeHorizontal: shape = IDC_SIZEWE;
				break;
			case Cursor::SizeVertical: shape = IDC_SIZENS;
				break;
			case Cursor::SizeTopLeftBottomRight: shape = IDC_SIZENWSE;
				break;
			case Cursor::SizeBottomLeftTopRight: shape = IDC_SIZENESW;
				break;
			case Cursor::SizeAll: shape = IDC_SIZEALL;
				break;
			case Cursor::Cross: shape = IDC_CROSS;
				break;
			case Cursor::Help: shape = IDC_HELP;
				break;
			case Cursor::NotAllowed: shape = IDC_NO;
				break;
		}

		cursor = CopyCursor(LoadCursor(nullptr, shape));

		if (!cursor) {
			XE_CORE_ERROR("[Win32Cursor]: Could not create copy of a system cursor");
			XE_ASSERT(cursor);
		}
	}

	Cursor::~Cursor() {
		release();
	}

	void Cursor::release() {
		if (cursor) {
			DestroyCursor(static_cast<HCURSOR>(cursor));
			cursor = nullptr;
		}
	}

}