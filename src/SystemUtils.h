#pragma once
#include "windows.h"
#include "Images.h"
#define PIXEL_SIZE 1
#define DISP_WIDTH 640
#define DISP_HEIGHT 480

void DrawBuffer(TImage Image);
void setHWND(HWND _Wnd);
