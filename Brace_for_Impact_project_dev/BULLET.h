#pragma once
#include <windows.h>
#include "Time.h"
#include <list>

//struct bullet{
//	double x;
//	double y;
//	double mx;
//	double my;
//	int type; // 0: 삭제   1~9: 플레이어용   10~:몬스터용
//	BOOL PlayerBullet;
//	bullet* next;
//}bullet;

class bullet {
private:
	double x;
	double y;
	double mx; // x 이동거리
	double my; // y 이동거리
	int type; // 0: 삭제   1~9: 플레이어용   10~:몬스터용


	BOOL PlayerBullet;
public:
	bullet ( double  , double  , int ,double  , double  );
	void Update ( );
	void move ( );
	void Render ( HDC dc );
	int return_type ( ) { return type; };
};

class BulletManager {
private:
	static std::list<bullet*> bullets;
public:
	 BulletManager();
	 static void Initailize (  HDC );
	static void Update ( );
	static void Render(HDC dc);
	static  void CreateBullet ( bullet*& newbullet );
	static void DeleteBullet ( );

};


