#pragma once
#pragma comment(lib, "msimg32.lib")
#include <Windows.h>
#include <list>
#include "SceneManager.h"
#include "Gameobject.h"
#include "Player1.h"
#include "enemy1.h"
#include "input.h"
#include "MONSTER.h"
#include "BULLET.h"
#include "Resource.h"
#include "Tank.h"

class Application {
private:
	Player1 player1;
	Player2 player2;
	Tank tank_p;
	HWND mHwnd;
	HDC hDC , mDC , hmemDC;
	RECT rt;
	HBITMAP mBackBitmap , mBitmap , B_Stage_1_1 , B_Stage_1_2 , B_Player , B_Tank_car , B_Tank_head;
	HBITMAP B_Machine[ 5 ];
	HBITMAP B_UI_info_up , B_UI_inside;
	HBITMAP B_ENEMY_1 , B_ENEMY_2 , B_PLAYER , B_BUILDING;
	HINSTANCE g_hinst;

	RECT r_stage = { 0, 0, 1024, 768 };			//스테이지 UI
	RECT r_info = { 0, 768, 1024, 1020 };		//정보 UI
	RECT r_car = { 1024, 510, 1680, 1020 };		//차체 UI
	RECT r_cannon = { 1124, 50, 1680, 460 };	//포신 UI
	RECT r_playground = { 1024, 0, 1680, 1020 };	//포신 UI

public:

	void f_Run ( );
	void f_Render ( );
	void f_Update ( );
	void f_FixedUpdate ( );
	void f_Initialize ( HWND hWnd , HINSTANCE );
};


