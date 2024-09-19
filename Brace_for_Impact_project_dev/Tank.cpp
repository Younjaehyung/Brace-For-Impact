#include "Tank.h"
#define TANKSIZE 128//192


Tank::Tank () {

	Tank_car_count = 0;
	Tank_head_count = 0;
	Tank_head_frame=2 , Tank_car_frame=0;
	Tank_car_direct=0 , Tank_head_direct=0;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	Tk_c_status=0;
	angle = 90;
	frameInterval=0;
	headMove = 0;
	fireInterval = 0;
	UnDieing = 0;
	OILMODE = 0;
}


void Tank::Clear ( )
{

	Tank_head_count = 0;
	Tank_head_frame = 2 , Tank_car_frame = 0;
	Tank_car_direct = 0 , Tank_head_direct = 0;		//0: 12시방향 1: 2시방향 2: 3시방향 3: 5시방향 4: 6시방향 6: 7시방향 7: 9시방향 8: 11시 방향
	Tk_c_status = 0;
	angle = 90;
	dashcnt2 = 0; dashcnt = 0;
	CannonInterval = 0;

	Tank_head_count = 0;
	Tank_car_count = 0;
	frameInterval = 0;
	shootingInterval = 0;
	fireInterval = 0;

	isMove = 0;		
	headMove = 0;	//탱크가 움직이고 있지 않으면 FRAME 0으로 만들 목적
	headArrow = 0;
	isHit = 0;
}

void Tank::Initialize (int type ) {
	
	if ( type == 1 || type == 2 ) {
		std::cout << "type" << std::endl;

		rect = { 0,(7*64),(2*64), (9*64) };
	}
	else if ( type == 3 || type == 4 ) {
		std::cout << "type" << std::endl;

		rect = { (15 * 64),( 29 * 64 ),( 17 * 64 ), ( 31 * 64 ) };

	}
	else if ( type == 5 || type == 6 ) {
		rect = { ( 0 * 64 )+1,( 10 * 64 ),( 2 * 64 )+1, (12 * 64 ) };

	}

	TankController::TankRects ( ) = rect;

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
	isMove = false;
	
		float speed = 250 * Time::DeltaTime ( );
		float moveX = 0;
		float moveY = 0;
		if ( TankController::Dash() ) {
			speed = 3*speed;
			//TankController::Dash() = 0 ;
			dashcnt+=  300* Time::DeltaTime ( );
			if ( dashcnt > 10 ) {
				dashcnt2++;
				bullet * newbullet = new bullet ( rect.left , rect.top , 200 , Tank_car_direct , Tank_head_direct );
				BulletManager::getInstance ( ).CreateBullet ( newbullet );
				dashcnt = 0;
				if ( dashcnt2 == 10 ) {
					TankController::Dash ( ) = 0;
					dashcnt2 = 0;
				}
			}
		}
		if ( TankController::WhoMoveStatus() == 1 ) {
			if ( input::GetKey ( eKeyCode::W ) ) {
				moveY -= 1;
				SoundManager::getInstance ( ).GetSoundID ( "Move" )->ReplaySound ( );
				isMove = true;
			}


			if ( input::GetKey ( eKeyCode::A ) ) {
				moveX -= 1;
				SoundManager::getInstance ( ).GetSoundID ( "Move" )->ReplaySound ( );
				isMove = true;
			}



			if ( input::GetKey ( eKeyCode::S ) ) {
				moveY += 1;
				SoundManager::getInstance ( ).GetSoundID ( "Move" )->ReplaySound ( );
				isMove = true;
			}



			if ( input::GetKey ( eKeyCode::D ) ) {
				moveX += 1;
				SoundManager::getInstance ( ).GetSoundID ( "Move" )->ReplaySound ( );
				isMove = true;
			}
		
		}
		else if ( TankController::WhoMoveStatus ( ) == 2 ) {
			if ( input::GetKey ( eKeyCode::UP ) ) {
				moveY -= 1;
				isMove = true;
			}


			if ( input::GetKey ( eKeyCode::LEFT ) ) {
				moveX -= 1;
				isMove = true;
			}



			if ( input::GetKey ( eKeyCode::DOWN ) ) {
				moveY += 1;
				isMove = true;
			}



			if ( input::GetKey ( eKeyCode::RIGHT ) ) {
				moveX += 1;
				isMove = true;
			}
		}

		if ( isMove ) {
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
					isMove = false;
					return;
				}
				
			}
			if ( isMove ) {
				rect.left += moveX;
				rect.right += moveX;
				rect.top += moveY;
				rect.bottom += moveY;
				TankController::TankOilCount ( );
				
			}
			
		}

		
		////손 때면
		//if ( input::GetKeyUp ( eKeyCode::W ) ) {
		//	
		//}
		//if ( input::GetKeyUp ( eKeyCode::A ) ) {
		//	
		//}
		//if ( input::GetKeyUp ( eKeyCode::S ) ) {
		//	
		//}
		//if ( input::GetKeyUp ( eKeyCode::D ) ) {
		//	
		//}

		//if ( input::GetKeyUp ( eKeyCode::W ) && input::GetKeyUp ( eKeyCode::A ) ) {
		//
		//}
		//if ( input::GetKeyUp ( eKeyCode::W ) && input::GetKeyUp ( eKeyCode::D ) ) {
		//	Tank_car_direct = 1;
		//	
		//}
		//if ( input::GetKeyUp ( eKeyCode::S ) && input::GetKeyUp ( eKeyCode::A ) ) {
		//	
		//}
		//if ( input::GetKeyUp ( eKeyCode::S ) && input::GetKeyUp ( eKeyCode::D ) ) {
		//	
		//}
		

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
		if ( TankController::WhoAimingStatus ( ) == 2 ) {
			if ( input::GetKey ( eKeyCode::RIGHT ) && TankController::TankAimingStatus ( ) ) {
				if ( ( frameInterval >= 0.1 ) ) {
					headMove = 1;
					headArrow = 0;

					frameInterval = 0;
				}
				frameInterval += Time::DeltaTime ( );
			}
			else if (   input::GetKey ( eKeyCode::LEFT ) && TankController::TankAimingStatus ( ) ) {
				if ( ( frameInterval >= 0.1 ) ) {
					headArrow = 1;
					headMove = 1;
					frameInterval = 0;
				}
				frameInterval += Time::DeltaTime ( );
			}
		}
		if ( TankController::WhoAimingStatus ( ) == 1 ) {
			if (   input::GetKey ( eKeyCode::D ) && TankController::TankAimingStatus ( ) ) {
				if ( ( frameInterval >= 0.1 ) ) {
					headMove = 1;
					headArrow = 0;

					frameInterval = 0;
				}
				frameInterval += Time::DeltaTime ( );
			}
			else if (  input::GetKey ( eKeyCode::A ) && TankController::TankAimingStatus ( ) ) {
				if ( ( frameInterval >= 0.1 ) ) {
					headArrow = 1;
					headMove = 1;
					frameInterval = 0;
				}
				frameInterval += Time::DeltaTime ( );
			}
		}
	}
	else {
		aiming_animation ( );
	}
	
}

void Tank::shooting ( ){
	
		if ( TankController::WhoAimingStatus ( ) == 2 &&input::GetKey ( eKeyCode::UP ) && TankController::TankAimingStatus ( )) {
			if ( shootingInterval >= 0.3 ) {
				
				shootingInterval = 0;

				if ( TankController::TankBullet() > 0 ) {
					fireInterval = 1;

					bullet* newbullet = new bullet ( rect.left + TANKSIZE / 2 + ( 40 * cos ( Radian_return ( angle ) ) ) , -10 + rect.top + TANKSIZE / 2 + ( 40 * -sin ( Radian_return ( angle ) ) ) , Tank_head_direct + 1 , cos ( Radian_return ( angle ) ) , -sin ( Radian_return ( angle ) ) );
					BulletManager::getInstance ( ).CreateBullet ( newbullet );
					TankController::TankBullet ( )--;
				}

			}
			shootingInterval += Time::DeltaTime ( );
				
		}
		else if ( TankController::WhoAimingStatus ( ) == 1 && input::GetKey ( eKeyCode::W ) && TankController::TankAimingStatus ( ) ) {
			if ( shootingInterval >= 0.3 ) {
				
				shootingInterval = 0;

				if ( TankController::TankBullet ( ) > 0 ) {
					fireInterval = 1;

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

void Tank::Update ( ){
	if ( !UnDieing ) {
		if ( TankController::TankHp ( ) > 0 ) { //디버그용으로 탱크 체력 0이여도 움직임 죽게하려면 ' = ' 만 뺄것
			aiming ( );
			shooting ( );
			if ( TankController::TankOil ( ) > 0 || OILMODE)
			{
				if ( TankController::TankMoveStatus ( ) ) {
					move ( );
				}
				moving_rander_cal ( );
			}
		}
		TankController::TankRects ( ) = rect;
	}
	else { //무적모드
		if ( TankController::TankHp ( ) <= 0 ) { 
			TankController::TankHp ( ) = 300;
		}
		aiming ( );
		shooting ( );
		if ( TankController::TankOil ( ) > 0 )
		{
			if ( TankController::TankMoveStatus ( ) ) {
				move ( );
			}
			moving_rander_cal ( );
		}
		TankController::TankRects ( ) = rect;
	}
}

void Tank::moving_rander_cal ( ) {
	if ( isMove ) {
		if ( TankController::WhoMoveStatus ( ) == 1 ) {
			if ( input::GetKey ( eKeyCode::W ) ) {
				Tank_car_direct = 0;

			}
			if ( input::GetKey ( eKeyCode::A ) ) {
				Tank_car_direct = 6;

			}
			if ( input::GetKey ( eKeyCode::S )  ) {
				Tank_car_direct = 4;

			}
			if ( input::GetKey ( eKeyCode::D ) ) {
				Tank_car_direct = 2;

			}

			if ( ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::A ) ) ) {
				Tank_car_direct = 7;


			}
			if ( ( input::GetKey ( eKeyCode::W ) && input::GetKey ( eKeyCode::D ) ) ) {
				Tank_car_direct = 1;

			}
			if ( ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::A ) )  ) {
				Tank_car_direct = 5;

			}
			if ( ( input::GetKey ( eKeyCode::S ) && input::GetKey ( eKeyCode::D ) ) ) {
				Tank_car_direct = 3;

			}
		}
		else if ( TankController::WhoMoveStatus ( ) == 2 ) {
			if ( input::GetKey ( eKeyCode::UP ) ) {
				Tank_car_direct = 0;

			}
			if ( input::GetKey ( eKeyCode::LEFT ) ) {
				Tank_car_direct = 6;

			}
			if (  input::GetKey ( eKeyCode::DOWN ) ) {
				Tank_car_direct = 4;

			}
			if ( input::GetKey ( eKeyCode::RIGHT ) ) {
				Tank_car_direct = 2;
				
			}

			if (  ( input::GetKey ( eKeyCode::UP ) && input::GetKey ( eKeyCode::LEFT ) ) ) {
				Tank_car_direct = 7;


			}
			if (  ( input::GetKey ( eKeyCode::UP ) && input::GetKey ( eKeyCode::RIGHT ) ) ) {
				Tank_car_direct = 1;

			}
			if (  ( input::GetKey ( eKeyCode::DOWN ) && input::GetKey ( eKeyCode::LEFT ) ) ) {
				Tank_car_direct = 5;

			}
			if (  ( input::GetKey ( eKeyCode::DOWN ) && input::GetKey ( eKeyCode::RIGHT ) ) ) {
				Tank_car_direct = 3;

			}
		}
		
	}





	if ( Tank_car_count >= 0.2 ) {
		Tank_car_frame++;
		if ( Tank_car_frame >= 6 ) Tank_car_frame = 0;
		Tank_car_count = 0;

		if ( isMove ) {
			TankController::TankStage_frame ( ).frame++;
			if ( TankController::TankStage_frame ( ).frame >= 4 ) TankController::TankStage_frame ( ).frame = 0;
			
		}
		

		//타이틀 화면 애니메이션 = 임시로 넣어뒀음. 나중에 타이틀.cpp에 넣어야 함
		


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
	
	
	
	if ( Debugging::ReturnMod ( ) ) {
		
		HPEN hPen = CreatePen ( PS_DOT , 1 , RGB ( 255 , 22 , 111 ) );

		HBRUSH myBrush = ( HBRUSH ) GetStockObject ( NULL_BRUSH );
		HBRUSH oldBrush = ( HBRUSH ) SelectObject ( mDC , myBrush );
		SelectObject ( mDC , hPen );
		Rectangle ( mDC , rect.left  , rect.top , rect.left + TANKSIZE , rect.top + TANKSIZE );
		DeleteObject ( hPen );
		hPen = CreatePen ( PS_DOT , 1 , RGB ( 125 , 212 , 111 ) );
		SelectObject ( mDC , hPen );
		SelectObject ( mDC , myBrush );

		Rectangle ( mDC , rect.left , rect.top , rect.right , rect.bottom );
		Rectangle ( mDC , rect.left , rect.top - 10 , rect.left + TANKSIZE , rect.top + TANKSIZE );

		SelectObject ( mDC , oldBrush );
		DeleteObject ( myBrush );
		DeleteObject ( hPen );
	}
}

void Tank::sound ( )
{
	SoundManager::getInstance ( ).GetSoundID ( "testMP3" )->ReplaySound ( );
	
	
}
