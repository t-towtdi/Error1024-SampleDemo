/*
	��� ����������� ����������� ������������� �� �������
*/

// ������� timeGetTime ������� ������ GetTickCount
#define _USE_TIMEGETTIME

#include "windows.h"

#ifdef _USE_TIMEGETTIME
#include "mmsystem.h"
#pragma comment(lib, "winmm")
#endif

static MSG Msg;

DWORD Time;
DWORD OldTime;

void SetMsg(MSG _Msg) {
	Msg = _Msg;
}

void SetPause(DWORD value) {
	if (value == 0) value = 1;
	Time = value;
#ifdef _USE_TIMEGETTIME
	timeBeginPeriod(1);		// ������������� ������������ �������� timeGetTime
	OldTime = timeGetTime() + Time;
#else
	OldTime = GetTickCount() + Time;
#endif
}

void Pause(void) {
	// ������� ����
	while (PeekMessage(&Msg, 0, 0, 0, PM_NOREMOVE) != 0) {
		if (GetMessage(&Msg, 0, 0, 0)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	
#ifdef _USE_TIMEGETTIME
	while (timeGetTime() < OldTime) Sleep(1);		// ���� ���� �� ������ ����� ���������� �����
	OldTime = timeGetTime() + Time;
#else
	while (GetTickCount() < OldTime) Sleep(1);		// ���� ���� �� ������ ����� ���������� �����
	OldTime = GetTickCount() + Time;
#endif
}
