#pragma once
#pragma comment(lib, "msimg32.lib")

#include <Windows.h>
#include <list>
//#include "SceneManager.h"
//#include "Gameobject.h"
//#include "PlayScenes.h"
#include "GameManager.h"
#include "input.h"

#include "Time.h"
#include "Texture.h"
#include "Sound.h"
class Application {
private:


	//타이틀 화면 애니메이션용 타이머

	HWND mHwnd;
	HDC hDC , mDC,GameDC;
	HINSTANCE g_hinst;
	int left;
	int Stage_num;
	int top;



	RECT rt;
	HBITMAP mBackBitmap , mBitmap , B_Stage_1_1 , B_Stage_1_2 , B_Player , B_Tank_car , B_Tank_head;
	RECT camera;

	BOOL gameStart = true;
	BOOL gameRule = false;


	//10: 스테이지1 전환 화면 11: 스테이지1
	//20: 스테이지2 전환화면 21: 스테이지2 30: 스테이지3 전환 31: 스테이지3
	//40: 스테이지4 전환 41: 스테이지4 50: 스테이지 5전환 51: 스테이지 5
	//60: 스테이지6 전환 61: 스테이지 6
	//0: 타이틀 화면 1: 게임룰 2: 게임 클리어 3: 게임 오버 4: 디버그
	int gameStatus = 0;
	int titleStatus = 0;

	RECT r_stage = { 0, 0, 1024, 768 };			//스테이지 UI
	RECT r_info = { 0, 768, 1024, 1020 };		//정보 UI			너비 1024 높이 252
	RECT r_car = { 1024, 510, 1680, 1020 };		//차체 UI
	RECT r_cannon = { 1124, 50, 1680, 460 };	//포신 UI
	RECT r_playground = { 1024, 0, 1680, 1020 };	//조종실 UI
	RECT r_canMove = { 1024 + 150 , 0 + 150 , 1024 + 550 , 0 + 100 + 750 };	//플레이어의 활동 가능 구역



public:
	Application ( ) {
		hDC = NULL;
		mDC = NULL;
		mBackBitmap = NULL;
	}
	void f_Run ( );
	void f_Render ( );
	void f_Update ( );
	void f_FixedUpdate ( );
	void f_Initialize ( HWND hWnd , HINSTANCE );
	void HandleResize ( );
	HINSTANCE ReturnHinstance ( ) { return g_hinst; }


};


