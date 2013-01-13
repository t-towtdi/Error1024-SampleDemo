#pragma once

typedef struct {
	int width;
	int height;
	unsigned char *pBitMap;
} TImage;

void imgClearRGBA(TImage Image, unsigned char R, unsigned char G, unsigned char B, unsigned char A);
void imgClear(TImage Image, unsigned long color);
