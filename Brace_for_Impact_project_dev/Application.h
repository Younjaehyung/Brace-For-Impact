#pragma once
#include <Windows.h>
#include <list>
#include "SceneManager.h"
#include "Gameobject.h"
#include "Player1.h"
#include "enemy1.h"
#include "input.h"
#include "MONSTER.h"
#include "BULLET.h"


class Application {
private:
	Player1 player1;
	Player2 player2;
	

	//enemy1 enemys[10];
	monster_manager monster_managers;
	//monster* monsterHD = NULL;
	//mop monsters;
	//bullet* AllBullet = NULL;
	bulletmanager BulletManager;

	HWND mHwnd;
	HDC hDC, mDC, hmemDC;
	RECT rt;
	HBITMAP mBackBitmap;
	HINSTANCE g_hinst;

	RECT r_stage = { 0, 0, 1024, 768 };			//스테이지 UI
	RECT r_info = { 0, 768, 1024, 1020 };		//정보 UI
	RECT r_car = { 1024, 510, 1680, 1020 };		//차체 UI
	RECT r_cannon = { 1124, 50, 1680, 460 };	//포신 UI

public:
	
	void f_Run();
	void f_Render();
	void f_Update();
	void f_FixedUpdate();
	void f_Initialize(HWND hWnd,HINSTANCE);
};

