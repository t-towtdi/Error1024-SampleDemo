#include "Pause.h"
#include "SystemUtils.h"
#include "Images.h"
#include "math.h"

static unsigned char BitMap[640 * 480 * 4];	// битовая карта изображения
static TImage Disp = {640, 480, BitMap};	// Изображение

static unsigned char SinT[256];				// Таблица синусов

static void CreateSinT(void) {
	int i;
	for (i = 0; i != 256; i++) {
		SinT[i] = (int)(sin((i * 3.14 * 2.0) / 256.0) * 128 + 128);
	}
}

void StartDemo(void) {
	int x, y, line;
	int tx1 = 0, ty1 = 0, tx2 = 0, ty2 = 0, tx3 = 0, ty3 = 0;
	int px1, py1, px2, py2, px3, py3;
	
	SetPause(16);	// fps ~= 60
	
	CreateSinT();
	
	//					AARRGGBB
	imgClear(Disp, 0xFF000000);		// очищаем экран
	
	while(1) {
		py1 = ty1;
		py2 = ty2;
		py3 = ty3;
	
		for (y = 0; y != Disp.height; y++) {
			line = y * Disp.width;
			px1 = tx1;
			px2 = tx2;
			px3 = tx3;
			
			for (x = 0; x != Disp.width; x++) {
				px1 = px1 + 1;
				px2 = px2 + 1;
				px3 = px3 + 1;
			
				Disp.pBitMap[((x + line) << 2) + 2] = (SinT[px1 & 255] + SinT[py1 & 255]) >> 1;	// R
				Disp.pBitMap[((x + line) << 2) + 1] = (SinT[px2 & 255] + SinT[py2 & 255]) >> 1;	// G
				Disp.pBitMap[((x + line) << 2) + 0] = (SinT[px3 & 255] + SinT[(py3 + 63) & 255]) >> 1;	// B
			}
			py1 = py1 + 1;
			py2 = py2 + 1;
			py3 = py3 + 1;
		}
		tx1 = tx1 + 1;
		ty1 = ty1 + 1;
		tx2 = tx2 + 2;
		ty2 = ty2 + 2;
		tx3 = ty3 + 3;
		ty3 = ty3 + 3;
		
		DrawBuffer(Disp);				// копируем в окно
		Pause();
	}
}
