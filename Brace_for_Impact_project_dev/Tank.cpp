#include "Tank.h"

Tank::Tank () {
	
}

void Tank::Init ( HINSTANCE g_hinst ) {
	B_Tank_car = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BITMAP9 ) ); //---1) 비트맵 로드하기
	B_Tank_head = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BITMAP10 ) ); //---1) 비트맵 로드하기

}


void Tank::move ( )
{
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::W ) ) {
		rect.top -= speed;
		rect.bottom -= speed;

	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		rect.left -= speed;
		rect.right -= speed;

	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		rect.top += speed;
		rect.bottom += speed;

	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		rect.left += speed;
		rect.right += speed;

	}


}

void Tank::shooting ( )
{
	
}

void Tank::Update ( )
{
	move ( );
}

void Tank::render (HDC hmemDC, HDC mDC)
{
	
	//탱크 몸통
	SelectObject ( hmemDC , ( HBITMAP ) B_Tank_car );
	TransparentBlt ( mDC , rect.left , rect.top , 128 , 128 , hmemDC , 0 , 0 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

	//탱크 머리
	SelectObject ( hmemDC , ( HBITMAP ) B_Tank_head );
	TransparentBlt ( mDC , rect.left , -10 + rect.top , 128 , 128 , hmemDC , 0 , 0 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

	//===



}
