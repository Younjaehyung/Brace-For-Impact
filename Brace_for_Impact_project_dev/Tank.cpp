#include "Tank.h"
#define TANKSIZE 128//192


Tank::Tank () {
	rect = {200,400,300,500};
	Tank_car_count = 0;
	Tank_head_count = 0;
	Tank_head_frame=2 , Tank_car_frame=0;
	Tank_car_direct=0 , Tank_head_direct=0;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	Tk_c_status=0;
	angle = 90;
	frameInterval=0;
	headMove = 0;
	fireInterval = 0;
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

	if ( TankController::TankMoveStatus ( ) ) {
		float speed = 200 * Time::DeltaTime ( );
		float moveX = 0;
		float moveY = 0;

		BOOL ckBlock[ 4 ] = { 0,0,0,0 }; // 0: 몹 위 , 1: 아래 , 2: 좌 , 3: 우
		/*for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
			if ( rect2rect ( ReturnRect ( ) , ScanBlock.ReturnRect ( ) ) ) {
				if ( ckMopUp ( ScanBlock.ReturnRect ( ) , ReturnRect ( ) ) ) {
					ckBlock[ 0 ] = 1;
				}
				if ( ckMopDown ( ScanBlock.ReturnRect ( ) , ReturnRect ( ) ) ) {
					ckBlock[ 1 ] = 1;
				}
				if ( ckMopLeft ( ScanBlock.ReturnRect ( ) , ReturnRect ( ) ) ) {
					ckBlock[ 2 ] = 1;
				}
				if ( ckMopRight ( ScanBlock.ReturnRect ( ) , ReturnRect ( ) ) ) {
					ckBlock[ 3 ] = 1;
				}
			}
		}*/

		if ( !ckBlock[ 0 ] ) {
			if ( input::GetKey ( eKeyCode::W ) &&rect.top>0) {
				moveY -= 1;
			}
		}
		if ( !ckBlock[ 2 ] ) {
			if ( input::GetKey ( eKeyCode::A ) &&rect.left > 0 ) {
				moveX -= 1;
			}
		}
		if ( !ckBlock[ 1 ] ) {
			if ( input::GetKey ( eKeyCode::S ) && rect.top<1650 ) {
				moveY += 1;
			}
		}
		if ( !ckBlock[ 3 ] ) {
			if ( input::GetKey ( eKeyCode::D ) && rect.left<1910) {
				moveX += 1;
			}
		}

		// Normalize the movement vector
		float magnitude = sqrt ( moveX * moveX + moveY * moveY );
		if ( magnitude > 0 ) {
			moveX = ( moveX / magnitude ) * speed;
			moveY = ( moveY / magnitude ) * speed;
		}
		for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
			RECTS recttemp = rect;
			RECTS block = ScanBlock.ReturnRect ( );
			recttemp.left += moveX;
			recttemp.right += moveX;
			recttemp.top += moveY;
			recttemp.bottom += moveY;
			if ( IntersectRect_float ( block , recttemp ) ) {
				return;
			}
		}
		rect.left += moveX;
		rect.right += moveX;
		rect.top += moveY;
		rect.bottom += moveY;



		if ( input::GetKey ( eKeyCode::W ) ) {
			Tank_car_direct = 0;
			isMove = true;
		}
		if ( input::GetKey ( eKeyCode::A ) ) {
			Tank_car_direct = 6;
			isMove = true;
		}
		if ( input::GetKey ( eKeyCode::S ) ) {
			Tank_car_direct = 4;
			isMove = true;
		}
		if ( input::GetKey ( eKeyCode::D ) ) {
			Tank_car_direct = 2;
			isMove = true;
		}

		if ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::A ) ) {
			Tank_car_direct = 7;
			isMove = true;

		}
		if ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::D ) ) {
			Tank_car_direct = 1;
			isMove = true;
		}
		if ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::A ) ) {
			Tank_car_direct = 5;
			isMove = true;
		}
		if ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::D ) ) {
			Tank_car_direct = 3;
			isMove = true;
		}


		//손 때면
		if ( input::GetKeyUp ( eKeyCode::W ) ) {
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::A ) ) {
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::S ) ) {
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::D ) ) {
			isMove = false;
		}

		if ( input::GetKeyUp ( eKeyCode::W ) && input::GetKeyUp ( eKeyCode::A ) ) {
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::W ) && input::GetKeyUp ( eKeyCode::D ) ) {
			Tank_car_direct = 1;
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::S ) && input::GetKeyUp ( eKeyCode::A ) ) {
			isMove = false;
		}
		if ( input::GetKeyUp ( eKeyCode::S ) && input::GetKeyUp ( eKeyCode::D ) ) {
			isMove = false;
		}
	}

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
		if ( input::GetKey ( eKeyCode::RIGHT ) && TankController::TankAimingStatus ( ) ) {
			if ( ( frameInterval >= 0.1  ) ) {
				headMove = 1;
				headArrow = 0;

				frameInterval = 0;
			}
			frameInterval += Time::DeltaTime ( );
		}
		else if ( input::GetKey ( eKeyCode::LEFT ) && TankController::TankAimingStatus ( ) ) {
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
		
		if ( input::GetKey ( eKeyCode::UP ) && TankController::TankAimingStatus ( )) {
			if ( shootingInterval >= 0.3 ) {
				fireInterval = 1;
				
				shootingInterval = 0;

				if ( TankController::TankBullet() > 0 ) {
					bullet* newbullet = new bullet ( rect.left + TANKSIZE / 2 + ( 40 * cos ( Radian_return ( angle ) ) ) , -10 + rect.top + TANKSIZE / 2 + ( 40 * -sin ( Radian_return ( angle ) ) ) , Tank_head_direct + 1 , cos ( Radian_return ( angle ) ) , -sin ( Radian_return ( angle ) ) );
					BulletManager::getInstance ( ).CreateBullet ( newbullet );
					TankController::TankBullet ( )--;
				}

			}
			shootingInterval += Time::DeltaTime ( );
				
		}
		else { shootingInterval = 0; }
			
			

		if ( fireInterval == 1 ) {
			if ( TankController::TankCannon_frame ( ).count >= 0.05 ) {
				TankController::TankCannon_frame ( ).frame++;
				TankController::TankCannon_frame ( ).count = 0;
				if ( TankController::TankCannon_frame ( ).frame > 4 ) {
					TankController::TankCannon_frame ( ).frame = 0;
					fireInterval = 0;
				}
				Tank_head_frame = 6;
				Tank_head_frame++;
				if(Tank_car_frame >= 8 ) Tank_head_frame = 0;
			}
			TankController::TankCannon_frame ( ).count += Time::DeltaTime ( );

		}
}

void Tank::Update ( )
{
	if ( TankController::TankHp ( ) >= 0 ) { //디버그용으로 탱크 체력 0이여도 움직임 죽게하려면 ' = ' 만 뺄것
		
		aiming ( );

		shooting ( );
		if ( TankController::TankOil ( ) >= 0  ) {

			move ( );
			moving_rander_cal ( );
		}
		

	}
}

void Tank::moving_rander_cal ( ) {
	
	if ( Tank_car_count >= 0.2 ) {
		Tank_car_frame++;
		if ( Tank_car_frame >= 6 ) Tank_car_frame = 0;
		Tank_car_count = 0;

		if ( isMove ) {
			TankController::TankStage_frame ( ).frame++;
			if ( TankController::TankStage_frame ( ).frame >= 4 ) TankController::TankStage_frame ( ).frame = 0;
			
		}
		

		//타이틀 화면 애니메이션 = 임시로 넣어뒀음. 나중에 타이틀.cpp에 넣어야 함
		TankController::ScreenTitle_frame ( ).frame++;
		if ( TankController::ScreenTitle_frame ( ).frame >= 5 ) TankController::ScreenTitle_frame ( ).frame = 0;



		if ( isHit ) {
			TankController::TankStage_frame ( ).frame = 5;
		}
		
	}
	Tank_car_count += Time::DeltaTime ( );
	
}

void Tank::Render ( const HDC& mDC)
{
	
	
	//탱크 몸통	
	TransparentBlt ( mDC , rect.left , rect.top , TANKSIZE , TANKSIZE , Texture::getInstance ( ).Texture_GetDC( "B_Tank_car" ) , Tank_car_frame * 128, Tank_car_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	
	//탱크 머리
	TransparentBlt ( mDC , rect.left ,  -10 + rect.top , TANKSIZE , TANKSIZE , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_head" ) , Tank_head_frame *128 , Tank_head_direct * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
	


}
