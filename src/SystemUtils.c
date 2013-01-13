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
	
	BitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// размер структуры
	BitMapInfo.bmiHeader.biWidth = Image.width;				// ширина картинки
	BitMapInfo.bmiHeader.biHeight = -Image.height;			// высота картинки, минус нужен чтобы изображение не было перевернутым
	BitMapInfo.bmiHeader.biPlanes = 1;						// количество слоев - всегда 1
	BitMapInfo.bmiHeader.biCompression = BI_RGB;			// формат
	BitMapInfo.bmiHeader.biSizeImage = Image.width * Image.height * 32 / 8;		// размер картинки
	
	StretchDIBits(
		DC, 
		0, 0, Image.width * PIXEL_SIZE, Image.height * PIXEL_SIZE,		// прямоугольник куда выводить
		0, 0, Image.width, Image.height,								// прямоугольник откуда выводить
		Image.pBitMap,													// указатель на массив пикселей
		&BitMapInfo,													// параметры 
		DIB_RGB_COLORS,													// формат вывода
		SRCCOPY);														// режим вывода
		
	ReleaseDC(Wnd, DC);
}
