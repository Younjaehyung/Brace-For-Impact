#pragma once
#pragma comment(lib,"winmm.lib")
#include <Windows.h>
#include <unordered_map>
#include <string>
#include <mmsystem.h>
#include "Resource.h"

class Texture {
private:
    Texture ( ) {};

   std::unordered_map<std::string , HBITMAP> idBitmap;
   std::unordered_map<std::string , HDC> idDC;

   HINSTANCE g_hinst;
public:
    static Texture& getInstance ( ) {
        static Texture instance;
        return instance;
    }

    void Sound_SetIT ( const HINSTANCE& inst ) {
        g_hinst = inst;
    }

    HINSTANCE& Sound_GetIT () {
        return g_hinst;
    }

    void Texture_Loading (const HDC& mDC , const HINSTANCE& g_hinst ) {
        Sound_SetIT ( g_hinst );
        HBITMAP mBitmap = CreateCompatibleBitmap ( mDC , 1024 * 2 , 1024 * 2 );
        idBitmap.emplace ( "GAME_FIELD" , mBitmap );

        //탱크와 플레이어 비트맵 선언
        idBitmap.emplace ( "B_Tank_car" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_CAR ) ) );
        idBitmap.emplace ( "B_Tank_head" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_HEAD ) ) );
        idBitmap.emplace ( "B_Player_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_Player_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_Bullet" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BULLET ) ) );
        idBitmap.emplace ( "B_Bullet_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BULLET_2 ) ) );
        idBitmap.emplace ( "B_Item" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ITEM ) ) );

        //UI 비트맵 선언
        idBitmap.emplace ( "B_UI_Info_up" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INFO_UP ) ) );
        idBitmap.emplace ( "B_UI_Inside" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INSIDE ) ) );
        idBitmap.emplace ( "B_UI_Stage" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_STAGE ) ) );
        idBitmap.emplace ( "B_UI_Cooltime" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_COOLTIME ) ) );
        idBitmap.emplace ( "B_UI_Status" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_STATUS ) ) );
        idBitmap.emplace ( "B_UI_Player" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_PLAYER ) ) );
        idBitmap.emplace ( "B_UI_Reloader" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_RELOADER ) ) );
        idBitmap.emplace ( "B_UI_Info" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INFO ) ) );
        idBitmap.emplace ( "B_Selectframe" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_SELECTFRAME ) ) );


        //조종기 오브젝트 비트맵 선언
        idBitmap.emplace ( "B_CT_Engine" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_ENGINE ) ) );
        idBitmap.emplace ( "B_CT_Move" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_MOVE ) ) );
        idBitmap.emplace ( "B_CT_Attack" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_ATTACK ) ) );
        idBitmap.emplace ( "B_CT_Steam_Dash" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_STEAM_DASH ) ) );
        idBitmap.emplace ( "B_CT_Cannon" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_CANNON) ) );
        idBitmap.emplace ( "B_CT_Itembox" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_CT_ITEMBOX ) ) );

        //스테이지 관련 비트맵 선언
        idBitmap.emplace ( "B_Building" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BUILDING ) ) );
        idBitmap.emplace ( "B_STAGE_1_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_1_1 ) ) );
        idBitmap.emplace ( "B_STAGE_1_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_1_2 ) ) );
        idBitmap.emplace ( "B_STAGE_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_2 ) ) );
        idBitmap.emplace ( "B_STAGE_3" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_3 ) ) );
        idBitmap.emplace ( "B_STAGE_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_1 ) ) );
        //적 비트맵 선언
        idBitmap.emplace ( "B_Enemy_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ENEMY_1 ) ) );
        idBitmap.emplace ( "B_Enemy_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ENEMY_2 ) ) );
        idBitmap.emplace ( "B_Enemy_3" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ENEMY_3 ) ) );
        idBitmap.emplace ( "B_Enemy_4" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ENEMY_4 ) ) );
        idBitmap.emplace ( "B_Enemy_5" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_ENEMY_5 ) ) );

        idBitmap.emplace ( "B_Boss_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_1 ) ) );
        idBitmap.emplace ( "B_Boss_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_2 ) ) );
        idBitmap.emplace ( "B_Boss_3" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_3 ) ) );
        idBitmap.emplace ( "B_Boss_4" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_4 ) ) );
        idBitmap.emplace ( "B_Boss_5" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_5 ) ) );
        idBitmap.emplace ( "B_Boss_6" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_BOSS_6 ) ) );
        //스크린 화면 출력
        idBitmap.emplace ( "B_TITLE" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_SCREEN_TITLE ) ) );
        idBitmap.emplace ( "B_Cursor" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_SCREEN_CURSOR ) ) );
        idBitmap.emplace ( "B_Select" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TITLE_SELECT ) ) );
        idBitmap.emplace ( "B_Clear" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_SCREEN_CLEAR ) ) );
        idBitmap.emplace ( "B_Rule" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_SCREEN_RULE ) ) );
        idBitmap.emplace ( "B_Over" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_SCREEN_OVER ) ) );
        idBitmap.emplace ( "B_Start" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGESTART ) ) );
        for ( const auto& pair : idBitmap ) {
            HDC memDC = CreateCompatibleDC ( mDC );
            SelectObject ( memDC , pair.second );
            idDC.emplace ( pair.first , memDC );
        }
    }

    const HDC& Texture_GetDC ( const std::string& name ) {
        auto it = idDC.find ( name );
        if ( it != idDC.end ( ) ) {
            return it->second;
        }
        return nullptr; 
    }

};


