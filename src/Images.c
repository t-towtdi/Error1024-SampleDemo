/*
	Images
*/
#include "Images.h"

void imgClearRGBA(TImage Image, unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
	int i;
	for (i = 0; i != Image.width * Image.height * 4; i = i + 4) {
		Image.pBitMap[i] 		= B;
		Image.pBitMap[i + 1]	= G;
		Image.pBitMap[i + 2]	= R;
		Image.pBitMap[i + 3]	= A;
	}
}

void imgClear(TImage Image, unsigned long color) {
	unsigned long *pBitMap;
	int i;
	pBitMap = (unsigned long*)Image.pBitMap;
	for (i = 0; i != Image.width * Image.height; i++) {
		pBitMap[i] = color;
	}
}
