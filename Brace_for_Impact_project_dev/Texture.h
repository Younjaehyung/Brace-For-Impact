#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>

class Texture {
protected:
    static std::unordered_map<std::string , HBITMAP> idBitmap;

public:
    void Texture_Loading ( HINSTANCE g_hinst ) {
        idBitmap.emplace ( "B_Tank_car" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_CAR ) ) );
        idBitmap.emplace ( "B_Tank_head" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_HEAD ) ) );
        idBitmap.emplace ( "B_Player_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_Player_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_STAGE_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_2 ) ) );
        idBitmap.emplace ( "B_UI_INFO_UP" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INFO_UP ) ) );
        idBitmap.emplace ( "B_UI_INSIDE" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INSIDE ) ) );


    }

    HBITMAP Texture_Getting ( const std::string& name ) {
        auto it = idBitmap.find ( name );
        if ( it != idBitmap.end ( ) ) {
            return it->second;
        }
        else {
            // 필요한 경우 에러 처리 로직 추가
            return nullptr;
        }
    }
};

// 클래스의 정적 멤버 변수 초기화
std::unordered_map<std::string , HBITMAP> Texture::idBitmap;
