/*
	√лавный модуль здесь мы создаем окно и запускаем саму демку
*/
#include "windows.h"
#include "windowsx.h"

#include "Demo.h"
#include "SystemUtils.h"
#include "Pause.h"

static HWND Wnd;
static MSG Msg;
static WNDCLASS wndclass;

/*
	ћы вручную перетаскиваем окно, т.к. если это будет делать Windows
	то при перетаскивании система забирает управление себе и демка "зависает".
	¬ыход - по правому клику
*/
static POINT MouseInWin;
static RECT WinRect;
static int MoveWin = 0;

// windows procedure
LONG WINAPI WndProc (
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	LONG lRet = 1;
	POINT point;
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		MoveWin = 1;	// move window = true
		GetWindowRect(Wnd, &WinRect);
		
		point.x = GET_X_LPARAM(lParam);
		point.y = GET_Y_LPARAM(lParam);
		ClientToScreen(Wnd, (LPPOINT)&point);
		
		MouseInWin.x = point.x - WinRect.left;
		MouseInWin.y = point.y - WinRect.top;
		
		SetCapture(Wnd);
		break;
	case WM_MOUSEMOVE:
		GetCursorPos((LPPOINT)&point);
		if (MoveWin) SetWindowPos(Wnd, 0, 
			point.x - MouseInWin.x, point.y - MouseInWin.y,
			WinRect.right - WinRect.left, WinRect.bottom - WinRect.top, 0);
		break;
	case WM_LBUTTONUP:
		MoveWin = 0;	// move window = false
		ReleaseCapture();
		break;
	case WM_RBUTTONUP:
		PostMessage(Wnd, WM_DESTROY, 0, 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ExitProcess(0);
		break;
	default:
		lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	
	return lRet;
}

void CreateWin(HINSTANCE hInstance, HWND* hWnd) {
	const int ClientWidth = DISP_WIDTH * PIXEL_SIZE;	// resolution * pizel size
	const int ClientHeight = DISP_HEIGHT * PIXEL_SIZE;
	
	RECT Rect = {0, 0, ClientWidth, ClientHeight};
	
	wndclass.style			= CS_BYTEALIGNCLIENT;
	wndclass.lpfnWndProc	= &WndProc;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= 0;
	wndclass.hIcon			= NULL;	//LoadIcon(0, L"idi_Application");
	wndclass.hCursor 		= LoadCursor(0, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName	= "";
	wndclass.lpszClassName  = "MainWindow";
	
	RegisterClass(&wndclass);
	
	Wnd = CreateWindow(
		"MainWindow",
		"Demo",
		WS_POPUPWINDOW,	// стиль
		CW_USEDEFAULT,	// x
		CW_USEDEFAULT,	// y
		ClientWidth,	// width
		ClientHeight,	// height
		0, 				// parent win
		0,				// menu
		hInstance,
		0				// other
	);
	
	GetWindowRect(Wnd, &Rect);
	Rect.bottom = Rect.left + ClientHeight;	// ClientHeight
	Rect.right = Rect.top + ClientWidth;	// ClientWidth
	AdjustWindowRect(&Rect, GetWindowLong(Wnd, GWL_STYLE), 0);
	
	SetWindowPos(Wnd, 0, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0);
	
	ShowWindow(Wnd, SW_SHOW);
	UpdateWindow(Wnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CreateWin(hInstance, &Wnd);		// создаем окно
	
	SetHWND(Wnd);
	SetMsg(Msg);
	
	StartDemo();
	
	return 0;
}
