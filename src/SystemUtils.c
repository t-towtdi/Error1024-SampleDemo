/*
	SystemUtils
*/
#include "windows.h"
#include "Images.h"
#include "SystemUtils.h"

static HWND Wnd;

void SetHWND(HWND _Wnd) {
	Wnd = _Wnd;
}

void DrawBuffer(TImage Image) {
	BITMAPINFO BitMapInfo;
	HDC DC;
	
	DC = GetDC(Wnd);
	
	BitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// ������ ���������
	BitMapInfo.bmiHeader.biWidth = Image.width;				// ������ ��������
	BitMapInfo.bmiHeader.biHeight = -Image.height;			// ������ ��������, ����� ����� ����� ����������� �� ���� ������������
	BitMapInfo.bmiHeader.biPlanes = 1;						// ���������� ����� - ������ 1
	BitMapInfo.bmiHeader.biCompression = BI_RGB;			// ������
	BitMapInfo.bmiHeader.biSizeImage = Image.width * Image.height * 32 / 8;		// ������ ��������
	
	StretchDIBits(
		DC, 
		0, 0, Image.width * PIXEL_SIZE, Image.height * PIXEL_SIZE,		// ������������� ���� ��������
		0, 0, Image.width, Image.height,								// ������������� ������ ��������
		Image.pBitMap,													// ��������� �� ������ ��������
		&BitMapInfo,													// ��������� 
		DIB_RGB_COLORS,													// ������ ������
		SRCCOPY);														// ����� ������
		
	ReleaseDC(Wnd, DC);
}
