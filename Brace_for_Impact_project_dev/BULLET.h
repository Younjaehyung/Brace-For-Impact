#pragma once
#include <windows.h>
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
	double mx;
	double my;
	int type; // 0: 삭제   1~9: 플레이어용   10~:몬스터용
	BOOL PlayerBullet;
public:
	bullet ( double  , double  , int ,double  , double  );
	void Update ( );
	void move ( );
	void rander ( HDC dc );
};

class BulletManager {
private:
	static std::list<bullet*> bullets;
public:
	BulletManager();
	static void rander(HDC dc);
	static void CreateBullet ( bullet*& newbullet );
	static void DeleteBullet ( );
	static void Update();
};


