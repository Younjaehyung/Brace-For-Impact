#include "Player1.h"
#define PLAYERSIZE 96


Player1::Player1() {
	rect = { 0,0,40,40 };
	count = 0;
	status = 0;
}

void Player1::Update ( ) {
	SwitchStatus ( );
	move ( );

}

void Player1::move ( ) {
	if ( TankController::TankMoveStatus ( ) ) {
		return;
	}

	float speed = 200 * Time::DeltaTime ( );

	if ( input::GetKey ( eKeyCode::W ) && rect.top > 0 ) { //  rect.top > 0
		if ( !((rect.left < 400 && rect.right > 220) && rect.top<460 && rect.top > 120) ) {
			rect.top -= speed;
			rect.bottom -= speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}
		
	}
	if ( input::GetKey ( eKeyCode::A ) && rect.left > 0) { // rect.left > 0
		if ( !(rect.top < 460 && rect.bottom > 120 && rect.left<400 && rect.left >220) ) {
			rect.left -= speed;
			rect.right -= speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
				direct = 0;
			}
			count += Time::DeltaTime ( );
		}
		
	}
	if ( input::GetKey ( eKeyCode::S ) && rect.bottom <900) { // rect.bottom < 900
		if ( !( rect.bottom < 460 && rect.bottom > 120 && rect.left < 400 && rect.right >220 ) ) {
			rect.top += speed;
			rect.bottom += speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}
		
	}
	if ( input::GetKey ( eKeyCode::D ) && rect.right <600) { // rect.right <600
		if ( !( rect.top < 460 && rect.bottom > 120 && rect.right < 400 && rect.right >220 ) ) {
			rect.left += speed;
			rect.right += speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
				direct = 1;
			}
			count += Time::DeltaTime ( );
		}

	}
	//플레이어1 충돌 범위

	if ( input::GetKeyUp ( eKeyCode::W ) || input::GetKeyUp ( eKeyCode::A ) || input::GetKeyUp ( eKeyCode::S ) || input::GetKeyUp ( eKeyCode::D ) ) {
		frame = 0;
	}

}

void Player1::SwitchStatus ( ) {
	if ( input::GetKeyUp ( eKeyCode::p1_a ) ) {
		if ( inrect_f ( 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 ,1024+ rect.left+20 , rect.top + 20 ) ) {
			TankController::TankMoveStatus ( ) = !TankController::TankMoveStatus ( );
			direct = 2;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			if ( status == 2 ) {
				status = 0;
				TankController::TankBullet ( )++;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			if ( status == 1 ) {
				status = 0;
				TankController::TankOil() += 50;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬

		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출

		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			status = 1;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			status = 2;
		}
	}
}

void Player1 :: Tank_control ( ) {

}

void Player1::FixedUpdate ( ) {
	p1Rect = { 1024 + rect.left , 0 + rect.top , 1024 + rect.left + PLAYERSIZE , 0 + rect.top + PLAYERSIZE };
}
void Player1::Render ( const HDC& mDC ) {
	//플레이어1
	
	TransparentBlt ( mDC , 1024 + rect.left,  0+ rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , frame * 64, direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	Rectangle ( mDC , rect.left , rect.top , rect.right+20, rect.bottom+20 );
	
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32, 0 + rect.top - 32 , PLAYERSIZE /2 , PLAYERSIZE /2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , frame * 64 , direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

	TCHAR a00[ 20 ]= L"sdsadsd";
	wsprintf ( a00 , L"%d  %d" , (int)(rect.left) , (int)(rect.top) );
	TextOut ( mDC , 1600 , 0 , a00 , 20 /*lstrlen ( a00 ) */ );
	//Rectangle ( mDC , 100,100,200,200 );

}
RECTS Player1::ReturnRect ( ) {
	return rect;
}





Player2::Player2() {
	rect = { 0,0,40,40 };
	count = 0;
	status = 0;
}

void Player2::Init ( HINSTANCE g_hinst ) {
	//B_Player_2 = ( HBITMAP ) LoadBitmap ( g_hinst , MAKEINTRESOURCE ( IDB_BM_PLAYER ) );	//youn
}

void Player2::Update() {
	SwitchStatus ( );
	move ( );

}
void Player2::move ( ) {

	if ( TankController::TankAimingStatus ( ) ) {
		return;
	}
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::UP ) && rect.top>0 ) { //rect.top > 0
		if ( !( ( rect.left < 400 && rect.right > 220 ) && rect.top < 460 && rect.top > 120 ) ) {
			rect.top -= speed;
			rect.bottom -= speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}
	}
	if ( input::GetKey ( eKeyCode::LEFT ) && rect.left>0 ) { // rect.left > 0
		if ( !( rect.top < 460 && rect.bottom > 120 && rect.left < 400 && rect.left >220 ) ) {
			rect.left -= speed;
			rect.right -= speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
				direct = 0;
			}
			count += Time::DeltaTime ( );
		}
	}
	if ( input::GetKey ( eKeyCode::DOWN ) && rect.bottom<900 ) { // rect.bottom < 900
		if ( !( rect.bottom < 460 && rect.bottom > 120 && rect.left < 400 && rect.right >220 ) ) {
			rect.top += speed;
			rect.bottom += speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}
	}
	if ( input::GetKey ( eKeyCode::RIGHT ) && rect.right < 600) { // rect.right < 600
		if ( !( rect.top < 460 && rect.bottom > 120 && rect.right < 400 && rect.right >220 ) ) {
			rect.left += speed;
			rect.right += speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
				direct = 1;
			}
			count += Time::DeltaTime ( );
		}
	}

	if ( input::GetKeyUp ( eKeyCode::UP ) || input::GetKeyUp ( eKeyCode::RIGHT ) || input::GetKeyUp ( eKeyCode::LEFT ) || input::GetKeyUp ( eKeyCode::DOWN ) ) {
		frame = 0;
	}
}
void Player2::SwitchStatus ( ) {
	if ( input::GetKeyUp ( eKeyCode::p2_a ) ) {
		if ( inrect_f ( 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 , 1024 +rect.left + 20 , rect.top + 20 ) ) {
			TankController::TankAimingStatus ( ) = !TankController::TankAimingStatus ( );
			direct = 2;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			if ( status == 2 ) {
				status = 0;
				TankController::TankBullet ( )++;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			if ( status == 1 ) {
				status = 0;
				TankController::TankOil ( ) += 50;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬

		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출

		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			status = 1;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			status = 2;
		}

	}
}

void Player2::FixedUpdate() {
}
void Player2::Render ( const HDC& mDC ) {
	//플레이어2
	
	TransparentBlt ( mDC , 1024 + rect.left,  0 +rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , frame * 64 , 64*4 + direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32 , 0 + rect.top - 32 , PLAYERSIZE / 2 , PLAYERSIZE / 2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) , frame * 64 , direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

}
RECTS Player2::ReturnRect() {
	return rect;
}