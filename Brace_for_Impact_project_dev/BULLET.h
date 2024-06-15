#pragma once
#include <windows.h>
#include "Time.h"
#include <list>
#include "Texture.h"

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

	float counter=0;

	float timer1;
	float timer2; //연막용 타이머
	float timer3; //피격용 타이머
	float timer4; //사망용 타이머
	int frame, gasframe;
	BOOL PlayerBullet;

	HBITMAP B_bullet;

public:
	bullet ( double  , double  , int ,double , double  );
	void Update ( );
	void move ( );
	void Render ( const HDC& );
	int return_type ( ) { return type; };
	int return_frame ( ) { return frame; };
};

class BulletManager {
private:
	BulletManager ( ) {
		deletetime = 0;
	};
	 std::list<bullet*> bullets;
	 float deletetime;
	 
public:
	static BulletManager& getInstance ( ) {
		static BulletManager instance;
		return instance;
	}


	//void Initailize ( const HDC& );
	void Update ( );
	void Render( const HDC& dc);
	void CreateBullet ( bullet*& newbullet );
	void DeleteBullet ( );

};


