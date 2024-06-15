#pragma once
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"
#include"BLOCK.h"

class GameManager
{
private:
	GameManager ( ) {
		score = 0;
		blackBrush = CreateSolidBrush ( RGB ( 20 , 20 , 20 ) );
		redBrush = CreateSolidBrush ( RGB ( 200 , 50 , 50 ) );
		cyanBrush = CreateSolidBrush ( RGB ( 0 , 120 , 140 ) );
	}
	RECT r_stage = { 0, 0, 1024, 768 };			//스테이지 UI
	RECT r_info = { 0, 768, 1024, 1020 };		//정보 UI			너비 1024 높이 252
	RECT r_car = { 1024, 510, 1680, 1020 };		//차체 UI
	RECT r_cannon = { 1124, 50, 1680, 460 };	//포신 UI
	RECT r_playground = { 1024, 0, 1680, 1020 };	//조종실 UI
	RECT r_canMove = { 1024 + 150 , 0 + 150 , 1024 + 550 , 0 + 100 + 750 };	//플레이어의 활동 가능 구역

	int score;
	int SceneStatus;
	int type;
	int End;

	float count;	//별 반짝이는 카운터
	bool Rule;	//Rule상태인가
	bool Selected;	//선택 상태인가
	int frame;	//별이 반짝이는 프레임
	int Cursor;		//커서 위치 바꾸는 인수

	HBRUSH blackBrush , redBrush , cyanBrush;
public:
	static GameManager& getInstance ( ) {
		static GameManager instance;
		return instance;
	}

	void Camera ( const HDC& mDC );
	void Camera_Cal ( const HDC& mDC );
	void Ground_Map ( const HDC& mDC );
	void Camera_UI_Ground ( const HDC& mDC );
	void Camera_UI_CT_1 ( const HDC& mDC );
	void Camera_UI_CT_2 ( const HDC& mDC );
	void Tank_Inside ( const HDC& mDC );

	void Clear ( )
	{
		MonsterManager::getInstance ( ).Clear ( );
		PlayerManager::getInstance ( ).Clear ( );
		BlockManager::getInstance ( ).Clear ( );
	}

	void Game_Initialize ( HDC mDC , HINSTANCE g_hinst )
	{
		Texture::getInstance ( ).Texture_Loading ( mDC , g_hinst );
		BulletManager::getInstance ( );
		MonsterManager::getInstance ( );
		PlayerManager::getInstance ( );
		BlockManager::getInstance ( );
	}

	void Scene_Initialize ( int Scene_num )
	{
		if ( !Scene_num ) {
		
			MonsterManager::getInstance ( ).Initialize ( Scene_num );
			PlayerManager::getInstance ( ).Initialize ( Scene_num );
			BlockManager::getInstance ( ).Initialize ( Scene_num );
		}
	}

	void Update ( )
	{
		if ( !type ) {
			return;
		}
		BulletManager::getInstance ( ).Update ( );
		MonsterManager::getInstance ( ).Update ( );
		PlayerManager::getInstance ( ).Update ( );

		
	}

	void Render ( const HDC& mDC , const HDC& orimDC )
	{
		if ( type == 0 ) {
			TitleScene ( mDC );
		}
		else if ( type == 10 ) {
			EndScene ( mDC );
		}
		else {
			GameRender ( mDC , orimDC );
		}
	}

	
	void GameRender ( const HDC& mDC , const HDC& orimDC ) {
		Ground_Map ( mDC );


		MonsterManager::getInstance ( ).Render ( mDC );
		BulletManager::getInstance ( ).Render ( mDC );
		BlockManager::getInstance ( ).Render ( mDC );
		Camera ( mDC );
		Camera_UI_Ground ( orimDC );
		Camera_UI_CT_1 ( orimDC );
		PlayerManager::getInstance ( ).Render ( mDC , orimDC );
		Camera_UI_CT_2 ( orimDC );
	}


	void TitleScene ( const HDC& );
	void EndScene ( const HDC& );

};

