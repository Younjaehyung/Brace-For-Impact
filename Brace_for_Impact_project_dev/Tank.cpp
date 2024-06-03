#include "Tank.h"
#define TANKSIZE 192


Tank::Tank () {
	rect = {};
	Tank_car_count = 0;
	Tank_head_count = 0;
	Tank_head_frame=2 , Tank_car_frame=0;
	Tank_car_direct=0 , Tank_head_direct=0;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	Tk_c_status=0;
	angle = 90;
	frameInterval=0;
	headMove = 0;
}


void Tank::move ( )
{
	//float speed = 200 * Time::DeltaTime ( );

	//if ( ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::A ) ) ||
	//   ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::D ) ) ||
	//   ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::A ) ) ||
	//   ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::D ) ) ) {
	//	
	//	speed /= sqrt ( 2 ); // 대각선 이동 시 속도 조정
	//}


	//if ( input::GetKey ( eKeyCode::W ) ) {
	//	rect.top -= speed;
	//	rect.bottom -= speed;
	//}
	//if ( input::GetKey ( eKeyCode::A ) ) {
	//	rect.left -= speed;
	//	rect.right -= speed;
	//}
	//if ( input::GetKey ( eKeyCode::S ) ) {
	//	rect.top += speed;
	//	rect.bottom += speed;
	//}
	//if ( input::GetKey ( eKeyCode::D ) ) {
	//	rect.left += speed;
	//	rect.right += speed;
	//	
	//}
	float speed = 200 * Time::DeltaTime ( );
	float moveX = 0;
	float moveY = 0;

	if ( input::GetKey ( eKeyCode::W ) ) {
		moveY -= 1;
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		moveX -= 1;
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		moveY += 1;
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		moveX += 1;
	}

	// Normalize the movement vector
	float magnitude = sqrt ( moveX * moveX + moveY * moveY );
	if ( magnitude > 0 ) {
		moveX = ( moveX / magnitude ) * speed;
		moveY = ( moveY / magnitude ) * speed;
	}

	rect.left += moveX;
	rect.right += moveX;
	rect.top += moveY;
	rect.bottom += moveY;

	moving_rander_cal ( );
}

void Tank::aiming_animation () {
	//if ( headMove == 1 ) {
		if ( headArrow == 0 && Tank_head_count >=0.05) {
			
			Tank_head_frame++;
			if ( Tank_head_frame > 4 ) {
				Tank_head_direct += 1;
				Tank_head_frame = 2;
				Tank_head_count = 0;
				headMove = 0;
				angle -= 45.0;
			}
			
			if ( Tank_head_direct > 7 ) {
				Tank_head_direct = 0;
			}
			Tank_head_count = 0;
		} 
		else if( headArrow == 1 && Tank_head_count >= 0.05 ) {
			
			Tank_head_frame--;
			if ( Tank_head_frame < 0 ) {
				Tank_head_direct -= 1;
				Tank_head_frame = 2;
				Tank_head_count = 0;
				headMove = 0;
				angle += 45.0;
			}
			
			if ( Tank_head_direct < 0 ) {
				Tank_head_direct = 7;
			}
			Tank_head_count = 0;
		}
		Tank_head_count += Time::DeltaTime ( );
	

	
}

void Tank::aiming ( ) {
	if ( headMove == 0 ) {
		if ( input::GetKey ( eKeyCode::RIGHT ) ) {
			if ( ( frameInterval >= 0.1  ) ) {
				headMove = 1;
				headArrow = 0;

				frameInterval = 0;
			}
			frameInterval += Time::DeltaTime ( );
		}
		else if ( input::GetKey ( eKeyCode::LEFT ) ) {
			if ( ( frameInterval >= 0.1  ) ) {
				headArrow = 1;
				headMove = 1;
				frameInterval = 0;
			}
			frameInterval += Time::DeltaTime ( );
		}
	}
	else {
		aiming_animation ( );
	}
	
}

void Tank::shooting ( )
{
		//OSW 24.06.02 20:12 탱크 존나 펑펑터지는 문제있음. 수정 필요함
		if ( input::GetKey ( eKeyCode::UP ) ) {
			if ( shootingInterval >= 0.3 ) {
				shootingInterval = 0;
				
				shootingInterval = 0;

			bullet* newbullet = new bullet ( rect.left + TANKSIZE/2 + ( 40 * cos ( Radian_return ( angle ) ) ) , -10 + rect.top + TANKSIZE /2 + ( 40 * -sin ( Radian_return ( angle ) ) ) , 5 , cos ( Radian_return ( angle ) ) , -sin ( Radian_return ( angle ) ) );
			BulletManager::getInstance().CreateBullet ( newbullet );
			}
			else{
				Cannon_frame++;

				if ( Cannon_frame > 4 ) Cannon_frame = 0;
				CannonInterval += Time::DeltaTime ( );
			}
			shootingInterval+= Time::DeltaTime ( );
			
		}
		else {
			Cannon_frame = 0;
			
			shootingInterval = 0;
		}
}

void Tank::Update ( )
{

	aiming ( );
	
	shooting ( );
	
	move ( );
	
}

void Tank::moving_rander_cal ( ) {
	
	if ( Tank_car_count >= 0.2 ) {
		Tank_car_frame++;
		if ( Tank_car_frame >= 6 ) Tank_car_frame = 0;
		Tank_car_count = 0;

		//탱크 움직일 때만 ui움직이도록 바꿀꺼임
		Stage_frame++;
		if ( Stage_frame >= 4 ) Stage_frame = 0;
	}
	Tank_car_count += Time::DeltaTime ( );
	
	if ( input::GetKey ( eKeyCode::W ) ) {
		Tank_car_direct = 0;
	}
	if ( input::GetKey ( eKeyCode::A ) ) {
		Tank_car_direct = 6;
	}
	if ( input::GetKey ( eKeyCode::S ) ) {
		Tank_car_direct = 4;
	}
	if ( input::GetKey ( eKeyCode::D ) ) {
		Tank_car_direct = 2;
	}

	if ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::A ) ) {
		Tank_car_direct = 7;
		isMove = true;

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
}

void Tank::Render ( const HDC& mDC)
{
	
	
	//탱크 몸통	
	TransparentBlt ( mDC , rect.left , rect.top , TANKSIZE , TANKSIZE , Texture::getInstance ( ).Texture_GetDC( "B_Tank_car" ) , Tank_car_frame * 128, Tank_car_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	
	//탱크 머리
	TransparentBlt ( mDC , rect.left , -10 + rect.top , TANKSIZE , TANKSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_head" ) , Tank_head_frame *128 , Tank_head_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	std::cout << rect.left << std::endl;
	
	



	

}
