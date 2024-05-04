#pragma once
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <random>
#include <sstream>

//랜덤함수 사용
std::random_device rd;
std::mt19937 gen(rd());


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM iParam);

HINSTANCE g_hinst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Brace for Impact";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hinst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);	// IDC_HAND
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //WHITE_BRUSH

	WndClass.lpszMenuName = MAKEINTRESOURCEW(IDC_EDITORWINDOW);


	WndClass.lpszClassName = lpszClass;

	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);	// IDI_QUESTION
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass,
		lpszWindowName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1980,
		1080,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);




	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

	//PeekMessage : 메시지큐에 메시지 유무에 상관없이 함수가 리턴됨
	//				리턴 값이 true일경우 메시지가 있고 false인 경우에는 메시지가 없다고 가르쳐준다



	while (true) {
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT) {
				break;
			}
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else {
			//메시지가 없을 경우 여기서 처리
			//게임 로직이 들어가면 된다.

		}
	}
	while (GetMessage(&Message, 0, 0, 0)) {
		
	}
	return Message.wParam;

}
