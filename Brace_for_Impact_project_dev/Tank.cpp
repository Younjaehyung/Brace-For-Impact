#include "Tank.h"

Tank::Tank () {
	Tank_car_count = 0;
	Tank_head_count = 0;
	Tank_head_frame=0 , Tank_car_frame=0;
	Tank_car_direct=0 , Tank_head_direct=0;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	Tk_c_status=0;
	angle = 90;
	frameInterval=0;
	headMove = 0;
}

void Tank::Initailize ( HINSTANCE g_hinst ) {
	angle = 90;
	 Tank_car_count=0;
	 Tank_head_count=0;
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

	moving_rander_cal ( );
}

void Tank::aiming_animation () {
	//if ( headMove == 1 ) {
		if ( headArrow == 0 && Tank_head_count >=0.03) {
			
			Tank_head_frame += 128;
			if ( Tank_head_frame >= 128 * 3 ) {
				Tank_head_direct += 1;
				Tank_head_frame = 0;
				Tank_head_count = 0;
				headMove = 0;
				angle -= 45.0;
			}

			if ( Tank_head_direct > 7 ) {
				Tank_head_direct = 0;
			}
			Tank_head_count = 0;
		}
		else if( headArrow == 1 && Tank_head_count >= 0.03 ) {
			
			Tank_head_frame -= 128;
			if ( Tank_head_frame <= 0 ) {
				Tank_head_direct -= 1;
				Tank_head_frame = 0;
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
	
		if ( input::GetKey ( eKeyCode::UP ) ) {
			if ( shootingInterval >= 0.5 ) {
				shootingInterval = 0;

			bullet* newbullet = new bullet ( rect.left + 64 + ( 40 * cos ( Radian_return ( angle ) ) ) , -10 + rect.top + 64 + ( 40 * -sin ( Radian_return ( angle ) ) ) , 10 , cos ( Radian_return ( angle ) ) , -sin ( Radian_return ( angle ) ) );
			BulletManager::CreateBullet ( newbullet );
			}
			shootingInterval+= Time::DeltaTime ( );
		}
		else {
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
	
	if ( Tank_car_count >= 0.3 ) {
		Tank_car_frame += 128;
		if ( Tank_car_frame >= 128 * 2 ) Tank_car_frame = 0;
		Tank_car_count = 0;
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

void Tank::Render (HDC mDC)
{

	//탱크 몸통
	Texture::Texture_Getting ( "B_Tank_car" );
	TransparentBlt ( mDC , rect.left , rect.top , 128 , 128 , hmemDC , Tank_car_frame, Tank_car_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

	//탱크 머리
	Texture::Texture_Getting ( "B_Tank_head" );
	TransparentBlt ( mDC , rect.left , -10 + rect.top , 128 , 128 , hmemDC , Tank_head_frame , Tank_head_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

	//===



}
