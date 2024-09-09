#pragma once
#include "Sound.h"
#include "MONSTER.h"
#include "BULLET.h"
#include "Player.h"
#include"BLOCK.h"
#include"Texture.h"
#include "TankController.h"
#include <random>

class GameManager
{
private:
	GameManager ( ) {
		score = 0;
		prevTankHp = 0;
		type = 0; Cursor = 0;
		frame = 0;
		Selected = 0;
		Stage_Switch_y;
		Stage_Switch_x=0;
		SceneStatus = 0;
		SceneCount = 7;
		Rule = 0;
		End = 0;
		BossSceneC = 0;
		BossSceneR = 0;
		blackBrush = CreateSolidBrush ( RGB ( 20 , 20 , 20 ) );
		redBrush = CreateSolidBrush ( RGB ( 200 , 50 , 50 ) );
		cyanBrush = CreateSolidBrush ( RGB ( 0 , 120 , 140 ) );
		TankInsideCamera = 0;
	}
	RECT r_stage = { 0, 0, 1024, 768 };			//스테이지 UI
	RECT r_info = { 0, 768, 1024, 1020 };		//정보 UI			너비 1024 높이 252
	RECT r_car = { 1024, 510, 1680, 1020 };		//차체 UI
	RECT r_cannon = { 1124, 50, 1680, 460 };	//포신 UI
	RECT r_playground = { 1024, 0, 1680, 1020 };	//조종실 UI
	RECT r_canMove = { 1024 + 150 , 0 + 150 , 1024 + 550 , 0 + 100 + 750 };	//플레이어의 활동 가능 구역

	int score;
	int SceneStatus;

	int BossSceneC;
	int BossSceneR;
	int type;
	int End;

	int Stage_Switch_y;
	int Stage_Switch_x ;
	float SceneCount;
	float SceneCount2;

	float count;	//별 반짝이는 카운터
	bool Rule;	//Rule상태인가
	bool Selected;	//선택 상태인가
	int frame;	//별이 반짝이는 프레임
	int Cursor;		//커서 위치 바꾸는 인수

	int engineframe;	
	float engineCount;

	int alertframe;
	float alertCount;

	int prevTankHp;	//이전 탱크 피
	bool invincibleMode;

	int endframe;
	float endcount;

	int CameraMx;
	int CameraMy;
	float TankInsideCamera;

	HBRUSH blackBrush , redBrush , cyanBrush, whiteBrush;

public:
	static GameManager& getInstance ( ) {
		static GameManager instance;
		return instance;
	}
	void Initialize ( ) {
		score = 0;
		type = 0; Cursor = 0;
		frame = 0;
		Selected = 0;
		Stage_Switch_y;
		Stage_Switch_x = 0;
		SceneStatus = 0;
		SceneCount = 7;
		Rule = 0;
		End = 0;
		BossSceneC = 0;
		BossSceneR = 0;
		blackBrush = CreateSolidBrush ( RGB ( 20 , 20 , 20 ) );
		redBrush = CreateSolidBrush ( RGB ( 200 , 50 , 50 ) );
		cyanBrush = CreateSolidBrush ( RGB ( 0 , 120 , 140 ) );
		whiteBrush = CreateSolidBrush ( RGB ( 255 , 255 , 255 ) );
		
	}
	void Camera ( const HDC& mDC );
	void Camera_Cal ( const HDC& mDC );
	void Ground_Map ( const HDC& mDC );
	void Camera_UI_Ground ( const HDC& mDC );
	void Camera_UI_CT_1 ( const HDC& mDC );
	void Camera_UI_CT_2 ( const HDC& mDC );
	void Tank_Inside ( const HDC& mDC );
	void ClearScene ( const HDC& mDC );
	void Clear ( )
	{
		MonsterManager::getInstance ( ).Clear ( );
		PlayerManager::getInstance ( ).Clear ( );
		BlockManager::getInstance ( ).Clear ( );
		BulletManager::getInstance ( ).Clear ( );
	
	}

	void Game_Initialize ( HDC mDC , HINSTANCE g_hinst )
	{
		Texture::getInstance ( ).Texture_Loading ( mDC , g_hinst );

		BulletManager::getInstance ( );
		MonsterManager::getInstance ( );
		PlayerManager::getInstance ( );
		BlockManager::getInstance ( );
		Stage_Sound ( );

	}

	void Scene_Initialize ( int Scene_num )
	{
		Clear ( );
		if ( Scene_num ) {
			TankController::Initialize ( );
			MonsterManager::getInstance ( ).Initialize ( Scene_num );
		
			PlayerManager::getInstance ( ).Initialize ( Scene_num );
			BlockManager::getInstance ( ).Initialize ( Scene_num );
		}
	}


	void Update ( )
	{
		if ( type==0&& End == 1 ) {
			Stage_Switch ( );
		}
		if ( TankController::TankHp ( ) <= 0 && SceneCount < 7 &&type!=0) {
			type = 10;
			return;
		}
		if ( !type ) {
			return;
		}
		
		Stage_condition ( );
		BulletManager::getInstance ( ).Update ( );
		MonsterManager::getInstance ( ).Update ( );
		PlayerManager::getInstance ( ).Update ( );
		
	}

	void Render ( const HDC& mDC , const HDC& orimDC )
	{
		if ( type == 0 && SceneStatus==0 ) {
			TitleScene ( orimDC );
			
		}
		else if ( type == 10 ) {
			EndScene ( orimDC );
		}
		else if ( type == 9 ) {
			ClearScene ( orimDC );
		}
		else {
			GameRender ( mDC , orimDC );
		}
	}

	
	void GameRender ( const HDC& mDC , const HDC& orimDC ) {
		Ground_Map ( mDC );
		Tank_Inside ( orimDC );
		MonsterManager::getInstance ( ).Render ( mDC );
		BulletManager::getInstance ( ).Render ( mDC );
	//	BlockManager::getInstance ( ).Render ( mDC );
		
		
		Camera_UI_CT_1 ( orimDC );
		PlayerManager::getInstance ( ).Render ( mDC , orimDC );

		if ( type == 0 && End == 1 ) {
			Stage_Switch_Render (mDC, orimDC );
		}
		else {
			Camera_Cal ( mDC );
			Camera ( orimDC );
		}
		
		Camera_UI_Ground ( orimDC );
		
		Camera_UI_CT_2 ( orimDC );
	}

	int& Return_SceneStatus ( ) {
		return SceneStatus;
	}

	bool& Return_invincibleMode ( ) {

		return invincibleMode;
	}

	void Stage_condition ( ) {
		if ( type == 9 || type == 10 ) {
			
			return;
		}

		if ( MonsterManager::getInstance ( ).MopReturn ( ).size ( ) == 0 ) {
			if ( SceneCount >= 4 ) {
				type = 0;
				End = 1;
				SceneCount = 0;
				SceneStatus += 1;
				SoundManager::getInstance ( ).StopAllChannels ( );
				if ( SceneStatus >= 7 ) {
					type = 9;
					End = 0;

					return;
				}
				Stage_Sound ( );
				Scene_Initialize ( SceneStatus );
				return;
			}
			SceneCount += Time::DeltaTime ( );
		}
			
	}

	void Stage_Sound ( ) {
		if ( SceneStatus == 0 ) {	//타이틀
			//SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE1 ) , Texture::getInstance().Sound_GetIT() , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 1) {	//스테이지1
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE2 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 2 ) {	//스테이지
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE3 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 3 ) {	//스테이지
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE4 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 4 ) {	
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE5 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 5 ) {
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE6 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		else if ( SceneStatus == 6 ) {
			SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->playSound ( );
			PlaySound ( MAKEINTRESOURCE ( IDR_WAVE7 ) , Texture::getInstance ( ).Sound_GetIT ( ) , SND_RESOURCE | SND_ASYNC | SND_LOOP );
		}
		


	}
	

	void Stage_Switch (  ) {

		if ( SceneCount >= 0.1 && 758 - 2 * Stage_Switch_y >= 758 - 384 ) {
			Stage_Switch_y+=6;
			Stage_Switch_x+=3;
			SceneCount = 0;
			
		}

		if ( SceneCount2 >= 6.0 ) {
			type = 1;
			End = 0;
			Stage_Switch_x = 0;
			Stage_Switch_y = 0;
			SceneCount2 = 0;
			BossSceneC++;
			if ( BossSceneC > 1 ) {
				BossSceneR++;
				BossSceneC = 0;
			}
			return;
		}
		SceneCount2 += Time::DeltaTime ( );
		SceneCount += Time::DeltaTime ( );
	}


	void TitleScene ( const HDC& );
	void MenuUpdate ( ) {
		if (( input::GetKeyDown ( eKeyCode:: DOWN ) || input::GetKeyDown ( eKeyCode::S )) && !Selected ) {
			if ( Cursor < 8 )
				Cursor += 4;
		}
		else if (( input::GetKeyDown ( eKeyCode::UP ) || input::GetKeyDown ( eKeyCode::W )) && !Selected ) {
			if ( Cursor > 0 )
				Cursor -= 4;
		}


		//게임 시작 창일때
		if (( input::GetKeyDown ( eKeyCode::F ) || input::GetKeyDown ( eKeyCode::M ) )&& Cursor == 0 ) {
			type = 1;
			
			return;
		}
		else if (( input::GetKeyDown ( eKeyCode::F ) || input::GetKeyDown ( eKeyCode::M ))&& Cursor == 4 ) {

			Rule = !Rule;

			if ( Rule ) {
				std::cout << "a" << std::endl;
				Selected = 1;
			}
			else {
				Selected = 0;
			}


		}
		else if(( input::GetKeyDown ( eKeyCode::M) || input::GetKeyDown ( eKeyCode::F )) && Cursor == 8 ){
			exit ( 1 );
		}
	}
	void EndScene ( const HDC& );
	void Stage_Switch_Render ( const HDC& mDC , const HDC& orimDC );

};

