#pragma once
#include <windows.h>
#include <list>
#include "Player1.h"
#include "MONSTER.h"

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
	double mx;
	double my;
	int type; // 0: 삭제   1~9: 플레이어용   10~:몬스터용
	BOOL PlayerBullet;
public:
	bullet ( double  , double  , double  , double  , int  );
	void Update ( );
	void move ( );
	void rander ( HDC dc );
};

class bulletmanager {
private:
	std::list<bullet*> bullets;
public:
	bulletmanager();
	void rander(HDC dc);
	static void CreateBullet (Player1& ,monster& m1 ,int );
	void DeleteBullet ( );
	void Update();
};

