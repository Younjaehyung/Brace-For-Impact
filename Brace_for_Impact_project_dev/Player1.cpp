#include "Player1.h"
#define PLAYERSIZE 96


Player1::Player1() {
	
	count = 0;
	status = 0;
}

void Player1::Clear ( ) {
	Ismove=0 , IsAiming=0;
	count = 0;
	status = 0;
	frame = 0;
	direct = 0;
	itemtype = 6;
	isHold = 0;
}

void Player1::Update ( ) {
	SwitchStatus ( );
	move ( );
	
}

void Player1::Initialize ( ) {
		
		rect = { 200,500,296,596 };
	
}

void Player1::move ( ) {
	if ( IsAiming || Ismove ) {
		return;
	}

	float speed = 200 * Time::DeltaTime ( );

	if ( input::GetKey ( eKeyCode::W )) { //  rect.top > 0
		
			rect.top -= speed;
			
			if ( rect.top <= 16 * 9 || ( IntersectRect_float ( rect , object1 ) ) ) {
				rect.top += speed;
				
			}
			else {
				rect.bottom -= speed;
				if ( count >= 0.1 ) {
					count = 0;
					frame++;
					if ( frame >= 5 ) frame = 0;
				}
				count += Time::DeltaTime ( );
			}
		
	}
	if ( input::GetKey ( eKeyCode::A )) { // rect.left > 0
		
			rect.left -= speed;
			
			if ( rect.left <= 16 * 6 || ( IntersectRect_float ( rect , object1 ) ) ) {
				rect.left += speed;
			}
			
			else {
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
	if ( input::GetKey ( eKeyCode::S )) { // rect.bottom < 900
			
			rect.bottom += speed;
			if ( rect.bottom >= 16*51   ) {
				rect.bottom -= speed;
			}
			else {
				rect.top += speed;

				if ( count >= 0.1 ) {
					count = 0;
					frame++;
					if ( frame >= 5 ) frame = 0;
				}
				count += Time::DeltaTime ( );
			}
			
		
		
	}
	if ( input::GetKey ( eKeyCode::D )) { // rect.right <600
			
			rect.right += speed;
			if (rect.right>=16*35 || ( IntersectRect_float ( rect , object1 ) ) ){

				rect.right -= speed;
			}
			else {
				rect.left += speed;
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
	if (isHold == false ) {
		if ( inrect_f ( 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//이동 조작
			itemtype = 3;
		}
		if ( inrect_f ( 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//공격 조종기
			itemtype = 3;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			itemtype = 3;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			itemtype = 3;//아무것도 안들고있음
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬
			itemtype = 3;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출
			itemtype = 3;
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			itemtype = 3;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			itemtype = 3;
		}
		else {
			itemtype = 6;
		}
	}
	

	if ( input::GetKeyUp ( eKeyCode::p1_a ) ) {
		if ( inrect_f ( 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			if ( !IsAiming && TankController::TankAimingStatus ( ) ) {	//조종안하고 있는데 작동중이면 리턴
				return;
			}
			TankController::TankAimingStatus ( ) = !TankController::TankAimingStatus ( );
			TankController::WhoAimingStatus ( ) = 1;
			IsAiming = !IsAiming;
			direct = 2;

		}
		if ( inrect_f ( 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {

			if ( !Ismove && TankController::TankMoveStatus ( ) ) {
				return;
			}
			TankController::TankMoveStatus ( ) = !TankController::TankMoveStatus ( );
			TankController::WhoMoveStatus ( ) = 1;
			Ismove = !Ismove;
			direct = 2;
		

		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			if ( status == 2 && itemtype == 1) {
				status = 0;
				itemtype = 6;
				isHold = false;
				TankController::TankBullet ( )++;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			if ( status == 1 && itemtype == 0) {
				status = 0;
				itemtype = 6;
				isHold = false;
				TankController::TankOil() += 50;
				if ( TankController::TankOil ( ) > 300 ) {
					TankController::TankOil ( ) = 300;
				}
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬
			if ( !TankController::Dash ( ) ) {
				TankController::Dash ( ) = 1;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출
			double angle = 45 * ( 3.141592 / 180 );
			for ( int i = 0; i < 8; i++ ) {
				bullet* newbullet = new bullet ( middleX ( TankController::TankRects ( ) ) + 150 * cos ( i * angle ) , middleY ( TankController::TankRects ( ) ) + 150 * sin ( i * angle ) , 100 , 0 , 0 );
				BulletManager::getInstance ( ).CreateBullet ( newbullet );
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			status = 1;
			itemtype = 0;
			isHold = true;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			status = 2;
			itemtype = 1;
			isHold = true;
		}
	}
}


void Player1::FixedUpdate ( ) {
	p1Rect = { 1024 + rect.left , 0 + rect.top , 1024 + rect.left + PLAYERSIZE , 0 + rect.top + PLAYERSIZE };
}
void Player1::Render ( const HDC& mDC ) {
	//플레이어1
	
	TransparentBlt ( mDC , 1024 + rect.left,  0+ rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_1" ) , frame * 64, direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	Rectangle ( mDC , rect.left , rect.top , rect.right+20, rect.bottom+20 );
	
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32, 0 + rect.top - 32 , 
		PLAYERSIZE /2 , PLAYERSIZE /2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) 
		, 0 * 64 , itemtype * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

	TCHAR a00[ 20 ]= L"sdsadsd";
	wsprintf ( a00 , L"%d  %d" , (int)(rect.left) , (int)(rect.top) );
	TextOut ( mDC , 1600 , 0 , a00 , 20 /*lstrlen ( a00 ) */ );
	//Rectangle ( mDC , 100,100,200,200 );

}
RECTS Player1::ReturnRect ( ) {
	return rect;
}





Player2::Player2() {

	count = 0;
	status = 0;
}

void Player2::Update() {
	SwitchStatus ( );
	move ( );

}
void Player2::move ( ) {

	if ( IsAiming || Ismove ) {
		return;
	}
	float speed = 200 * Time::DeltaTime ( );
	if ( input::GetKey ( eKeyCode::UP ) ) { //rect.top > 0
		rect.top -= speed;

		if ( rect.top <= 16 * 9 || ( IntersectRect_float ( rect , object1 ) ) ) {
			rect.top += speed;

		}
		else {
			rect.bottom -= speed;
			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}

		
	}
	if ( input::GetKey ( eKeyCode::LEFT )  ) { // rect.left > 0
		rect.left -= speed;

		if ( rect.left <= 16 * 6 || ( IntersectRect_float ( rect , object1 ) ) ) {
			rect.left += speed;
		}

		else {
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
	if ( input::GetKey ( eKeyCode::DOWN )  ) { // rect.bottom < 900
		rect.bottom += speed;
		if ( rect.bottom >= 16 * 51 ) {
			rect.bottom -= speed;
		}
		else {
			rect.top += speed;

			if ( count >= 0.1 ) {
				count = 0;
				frame++;
				if ( frame >= 5 ) frame = 0;
			}
			count += Time::DeltaTime ( );
		}

	}
	if ( input::GetKey ( eKeyCode::RIGHT)) { // rect.right < 600
		rect.right += speed;
		if ( rect.right >= 16 * 32 || ( IntersectRect_float ( rect , object1 ) )  ) {

			rect.right -= speed;
		}
		else {
			rect.left += speed;
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
	//조종기 범위 내에서 F와 M나타나기
	if ( isHold == false ) {
		if ( inrect_f ( 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//이동 조작
			itemtype = 4;
		}
		if ( inrect_f ( 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//공격 조종기
			itemtype = 4;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			itemtype = 4;
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			itemtype = 4;//아무것도 안들고있음
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬
			itemtype = 4;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출
			itemtype = 4;
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			itemtype = 4;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			itemtype = 4;
		}
		else {
			itemtype = 6;
		}
	}
	


	if ( input::GetKeyUp ( eKeyCode::p2_a ) ) {
		
		if ( inrect_f ( 1024 + 16 * 26 , 16 * 9 , 1024 + 16 * 34 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			if ( !IsAiming && TankController::TankAimingStatus ( ) ) {	//조종안하고 있는데 작동중이면 리턴
				return;
			}
			TankController::TankAimingStatus ( ) = !TankController::TankAimingStatus ( );
			TankController::WhoAimingStatus ( ) = 2;
			IsAiming = !IsAiming;
			direct = 2;
			
		}
		if ( inrect_f ( 1024 + 16 * 8 , 16 * 9 , 1024 + 16 * 16 , 16 * 18 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			
			if ( !Ismove && TankController::TankMoveStatus ( ) ) {
				return;
			}
			TankController::TankMoveStatus ( ) = !TankController::TankMoveStatus ( );
			TankController::WhoMoveStatus ( ) = 2;
			Ismove = !Ismove;
			direct = 2;

		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 28 , 1024 + 16 * 26 , 16 * 35 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//장전
			if ( status == 2 && itemtype == 1) {
				status = 0;
				isHold = false;
				itemtype = 6;
				TankController::TankBullet ( )++;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 16 , 16 * 46 , 1024 + 16 * 26 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료충전
			if ( status == 1  && itemtype == 0) {
				status = 0;
				itemtype = 6;//아무것도 안들고있음
				isHold = false;
				TankController::TankOil ( ) += 50;
				if ( TankController::TankOil ( ) > 300 ) {
					TankController::TankOil ( ) = 300;
				}
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 46 , 1024 + 16 * 16 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//대쉬
			if ( !TankController::Dash ( ) ) {
				TankController::Dash ( ) = 1;
			}
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 46 , 1024 + 16 * 34 , 16 * 54 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//증기분출
			double angle = 45 * ( 3.141592 / 180 );
			for ( int i = 0; i < 8; i++ ) {
				bullet* newbullet = new bullet ( middleX ( TankController::TankRects ( ) )+150*cos(i*angle ) , middleY ( TankController::TankRects ( ) )+150*sin ( i * angle ) , 100 , 0 , 0 );
				BulletManager::getInstance ( ).CreateBullet ( newbullet );
			}
		}
		else if ( inrect_f ( 1024 + 16 * 8 , 16 * 34 , 1024 + 16 * 15 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//연료 저장고
			itemtype = 0;
			isHold = true;
			status = 1;
		}
		else if ( inrect_f ( 1024 + 16 * 26 , 16 * 34 , 1024 + 16 * 34 , 16 * 40 , 1024 + rect.left + 20 , rect.top + 20 ) ) {
			//탄약 저장고
			itemtype = 1;
			isHold = true;
			status = 2;
		}

	}
}

void Player2::Clear ( ) {
	Ismove = 0 , IsAiming = 0;
	count = 0;
	status = 0;
	frame = 0;
	direct = 0;
	itemtype = 6;
	isHold = 0;

}
void Player2::Initialize (  ) {

	rect = { 200,500,296,596 };

}

void Player2::FixedUpdate() {
}
void Player2::Render ( const HDC& mDC ) {
	//플레이어2
	
	TransparentBlt ( mDC , 1024 + rect.left,  0 +rect.top, PLAYERSIZE , PLAYERSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Player_2" ) , frame * 64 , 64*4 + direct * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
	//플레이어가 아이템을 들었을 때 출력 할 아이템 이미지
	TransparentBlt ( mDC , 1024 + rect.left + 32 , 0 + rect.top - 32 , 
		PLAYERSIZE / 2 , PLAYERSIZE / 2 , Texture::getInstance ( ).Texture_GetDC ( "B_Item" ) 
		, 0 * 64 , itemtype * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

}
RECTS Player2::ReturnRect() {
	return rect;
}