#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>
#include "Resource.h"

class Texture {
private:
    Texture ( ) {};

   std::unordered_map<std::string , HBITMAP> idBitmap;
   std::unordered_map<std::string , HDC> idDC;


public:
    static Texture& getInstance ( ) {
        static Texture instance;
        return instance;
    }

    void Texture_Loading (const HDC& mDC , const HINSTANCE& g_hinst ) {
        
        idBitmap.emplace ( "B_Tank_car" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_CAR ) ) );
        idBitmap.emplace ( "B_Tank_head" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_TANK_HEAD ) ) );
        idBitmap.emplace ( "B_Player_1" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_Player_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) ) );
        idBitmap.emplace ( "B_STAGE_2" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_STAGE_2 ) ) );
        idBitmap.emplace ( "B_UI_INFO_UP" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INFO_UP ) ) );
        idBitmap.emplace ( "B_UI_INSIDE" , ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_UI_INSIDE ) ) );

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


