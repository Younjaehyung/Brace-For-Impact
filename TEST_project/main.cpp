/*
main.cpp

*/

#include "stdfx.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, oldBrush;
	RECT rt;
	HDC mDC;
	HBITMAP hbitmap;
	int mx, my;

	switch (iMessage) {
	case WM_CREATE:

		break;
	case WM_PAINT:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {

		}


		GetClientRect(hWnd, &rt);
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		hbitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
		SelectObject(mDC, (HBITMAP)hbitmap);
		
		RECta





		BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC);
		DeleteObject(hbitmap);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		
		break;
	case WM_LBUTTONUP:

		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		
		break;

	case WM_COMMAND:
		break;
	case WM_CHAR:
		
		break;


	case WM_KEYDOWN:



		break;
	case WM_TIMER:

		break;
	case WM_DESTROY:
		
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

