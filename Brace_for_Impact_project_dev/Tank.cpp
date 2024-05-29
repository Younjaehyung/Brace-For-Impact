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
	Tank_car_frame += 128;
	if ( Tank_car_frame >= 128 * 4 ) Tank_car_frame = 0;
	float speed = 5000 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::A ) ) {
		Tank_car_direct = 7;
	}
	if ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::D ) ) {
		Tank_car_direct = 1;
	}
	if ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::A ) ) {
		Tank_car_direct = 5;
	}
	if ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::D ) ) {
		Tank_car_direct = 3;
	}


	if ( input::GetKey ( eKeyCode::W ) && !input::GetKey ( eKeyCode::D )  && !input::GetKey ( eKeyCode:: A ) ) {
		Tank_car_direct = 0;
	}
	if ( input::GetKey ( eKeyCode::A ) && !input::GetKey ( eKeyCode::W ) && !input::GetKey ( eKeyCode::S ) ) {
		Tank_car_direct = 6;
	}
	if ( input::GetKey ( eKeyCode::S ) && !input::GetKey ( eKeyCode::D ) && !input::GetKey ( eKeyCode::A ) ) {
		Tank_car_direct = 4;
	}
	if ( input::GetKey ( eKeyCode::D ) && !input::GetKey ( eKeyCode::W ) && !input::GetKey ( eKeyCode::S ) ) {
		Tank_car_direct = 2;
	}


	if ( input::GetKey ( eKeyCode::LEFT ) ) {
		Tank_head_direct += 1;
		if ( Tank_head_direct > 7 ) {
			Tank_head_direct = 0;
		}
	}
	if ( input::GetKey ( eKeyCode::RIGHT ) ) {
		Tank_head_direct -= 1;
		if ( Tank_head_direct < 0 ) {
			Tank_head_direct = 7;
		}
	}

	//탱크 몸통
	SelectObject ( hmemDC , ( HBITMAP ) B_Tank_car );
	TransparentBlt ( mDC , rect.left , rect.top , 128 , 128 , hmemDC , Tank_car_frame, Tank_car_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

	//탱크 머리
	SelectObject ( hmemDC , ( HBITMAP ) B_Tank_head );
	TransparentBlt ( mDC , rect.left , -10 + rect.top , 128 , 128 , hmemDC , Tank_head_direct * 64 , 0 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

	//===



}
