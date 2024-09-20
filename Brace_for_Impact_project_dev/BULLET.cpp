#include "BULLET.h"
#include "MATH.h"
#include <random>
#include"BLOCK.h"
#include "Player.h"
#include"MONSTER.h"

#define SIZE 20
HDC cpyDC;
HWND hwnd;

bullet::bullet ( double dx, double dy, int dtype, double dmx, double dmy)
:x(dx),y(dy),mx(dmx),my(dmy),type(dtype){
	if ( (dtype > 0 && dtype < 10) || dtype==100 ||dtype==200) PlayerBullet = 1;
	// 0: 삭제   1~9: 플레이어용   10~:몬스터용 
	// 1~9 :플레이어 탄   100: 연막
	//10: 기본탄 1 데미지
	//11: 강력탄 10 데미지
	//12: 분열탄 맞을 시 8방향으로 나뉨
	//13: 회전탄 회전하면서 날아감
	//14: 충격파 제자리에서 점점 커짐
	//15: 데미지 입히는 지형 생성
}



void bullet::move ( ) {
	//자폭이꺼
	if ( type == 14) {
		counter += 100 * Time::DeltaTime ( );
	}
	//장판뎀
	else if ( type == 15 ) {
		counter += 10 * Time::DeltaTime ( );
	}
	//연기
	else if ( type == 100 ) {
		counter += 10 * Time::DeltaTime ( );
	}
	//대쉬
	else if ( type == 200 ) {
		counter += 10 * Time::DeltaTime ( );
	}
	//모든 총알
	else {
		if ( type != 0 ) {
			x += mx * 600 * Time::DeltaTime ( );
			y += my * 600 * Time::DeltaTime ( );
		}
	}
		//총알 프레임
	if ( type != 0 ) {
		if ( timer1 > 0.1 ) {
			frame++;

			if ( type == 100 ) {
				for ( auto& ScanMop : MonsterManager::getInstance ( ).MopReturn ( ) ) {
					if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE ) && ScanMop->ReturnHP ( ) > 0 ) {
						if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE + counter ) && ScanMop->ReturnHP ( ) > 0 ) {
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							ScanMop->Damage ( 5 );
						}
					}
				}
			}
			if ( frame >= 2 ) frame = 0;
			timer1 = 0;
		}timer1 += Time::DeltaTime ( );
	}
	else {
		if ( timer1 > 0.1 ) {
			frame++;
			timer1 = 0;
		}timer1 += Time::DeltaTime ( );
	}

		if ( x < 0 || y < 0 ) {
			type = 0;
		}
		if ( type > 0 ) {
			//벽에 탄 맞음
			for ( auto& ScanBlock : BlockManager::getInstance ( ).BlockReturn ( ) ) {
				if ( rect2Cir ( ScanBlock.ReturnRect ( ) , x , y , SIZE ) ) {
					type = 0;
					frame = 0;
				}
			}

			//몬스터가 탄 맞음
			if ( PlayerBullet ) {
				for ( auto& ScanMop : MonsterManager::getInstance ( ).MopReturn ( ) ) {
					if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE ) && ScanMop->ReturnHP ( ) > 0 ) {
						if ( type != 100 && type!=200) {
							type = 0;
							frame = 0;
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							ScanMop->Damage ( 30 );
						}
						else if(type==100){ //연막
							if ( counter >= 14 ) {
								if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE + counter ) && ScanMop->ReturnHP ( ) > 0 ) {
									ScanMop->Damage ( 1 );
								}
							}
							if ( counter >= 15 ) {
								if ( rect2Cir ( ScanMop->ReturnRect ( ) , x , y , SIZE + counter ) && ScanMop->ReturnHP ( ) > 0 ) {
									ScanMop->Damage ( 1 );
								}
								type = 0;
							}
						}
					}
				}
				if ( type==100 &&counter >= 15 ) {
					type = 0;
				}
				else if ( type == 200 && counter >= 10 ) {
					type = 0;
				}
			}
			//플레이어(탱크)가 탄 맞음
			if ( !PlayerBullet ) {
				RECTS tankrect = PlayerManager::getInstance ( ).Tank_return ( ).ReturnRect ( );
				if ( type == 14 ) {
					if ( counter >= 500 ) {
						if ( rect2Cir ( tankrect , x , y , SIZE + counter ) && TankController::TankHp ( ) > 0 ) {
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							TankController::Damage ( 100 );
						}
						type = 0;
					}
				}
				else if ( type == 15 ) {
					if ( counter >=  20) {
						if ( rect2Cir ( tankrect , x , y , 6*SIZE ) && TankController::TankHp ( ) > 0 ) {
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							TankController::Damage ( 100 );
						}
						type = 0;
					}
				}
				else {
					
					if ( rect2Cir ( tankrect , x , y , SIZE ) && TankController::TankHp ( ) > 0 ) {
						if ( type == 10 ) { //오줌이
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							TankController::Damage ( 1 );
						}
						else if ( type == 11 ) {//빵빵이
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							TankController::Damage ( 45 );
						}
						else if ( type == 12 ) {//춘식이
							SoundManager::getInstance ( ).GetSoundID ( "Hit" )->ReplaySound ( );
							TankController::Damage ( 40 );
							
						}
						type = 0;
					}
				}
			}
		}
	
}


void bullet::Render ( const HDC& dc ) {
	if ( type != 0 ) {
		if ( PlayerBullet ) { //플레이어가 쏜 총알
			if ( type != 100 && type != 200 ) {
				TransparentBlt ( dc , x - 4 * SIZE , y - 4 * SIZE , SIZE * 8 , SIZE * 8 ,
					Texture::getInstance ( ).Texture_GetDC ( "B_Bullet" ) , frame * 64 , ( type - 1 ) * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			}
			else if(type==100) { //연막
				//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
				TransparentBlt ( dc , x - SIZE*4 - counter, y - SIZE*4 - counter , SIZE * 8 + counter * 2 , SIZE * 8 + counter * 2 ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet" ) , gasframe*64 , 8 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );

			}
			else { //대쉬

				BLENDFUNCTION bf;
				bf.BlendOp = AC_SRC_OVER;
				bf.BlendFlags = 0;
				bf.AlphaFormat = 0;
				bf.SourceConstantAlpha = 200-counter*15;
				
				BitBlt ( dc , 0 , 0 , 128 , 128 , dc , x , y , SRCCOPY );
				TransparentBlt ( dc , 0,0 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_car" ) , 1 * 128 , mx * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				TransparentBlt ( dc , 0 , -10 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_head" ) , 1 * 128 , my * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
				
				AlphaBlend ( dc , x , y , 128 , 128 , dc ,0,0 , 128 , 128 , bf );
				TransparentBlt ( dc , 0 , 0 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 / 2 , 0 / 2 , 128 / 2 , 128 / 2 , RGB ( 255 , 255 , 255 ) );

			}
			//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
		}
		else { // 몬스터가 쏜 총알
			if ( type == 14 ) { // 자폭이 폭발
				TransparentBlt ( dc , (int)(x -  SIZE -counter) , ( int )( y - SIZE-counter) , ( int )(2*( SIZE +counter)) , ( int )( 2*( SIZE +counter)) ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 3 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
				//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
			}
			else if (type == 10 ) { //오줌이
				TransparentBlt ( dc , ( int )( x - 4 * SIZE) , ( int )( y - 4 * SIZE ), ( int )( SIZE * 8 ), ( int )( SIZE * 8) ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 0 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( type == 15 ) { //오줌이 장판
				Ellipse ( dc , x - 6*SIZE , y - 6*SIZE  , x + 6*SIZE , y + 6*SIZE  );
			}
			else if ( type == 11) { //빵빵이
				TransparentBlt ( dc , ( int )( x - 4 * SIZE ), ( int )( y - 4 * SIZE) , ( int )( SIZE * 8) , ( int )( SIZE * 8) ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 2 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			}
			else if ( type == 12 ) { //춘식이
				TransparentBlt ( dc , ( int )( x - 4 * SIZE) , ( int )( y - 4 * SIZE ), ( int )(SIZE * 8) , ( int )(SIZE * 8) ,
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 1 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			}
			else { //그 외 다른애들 총알
				TransparentBlt ( dc , ( int )( x - 4 * SIZE) , ( int )( y - 4 * SIZE) , ( int )(SIZE * 8) , ( int )(SIZE * 8 ),
				Texture::getInstance ( ).Texture_GetDC ( "B_Bullet_2" ) , frame * 64 , 0 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
				//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
			}
		}
	}
	else {
		if ( PlayerBullet ) {
				TransparentBlt ( dc , x - 4 * SIZE , y - 4 * SIZE , SIZE * 8 , SIZE * 8 ,
						Texture::getInstance ( ).Texture_GetDC ( "B_Bullet" ) , frame * 64 , 9 * 64 , 64 , 64 , RGB ( 255 , 255 , 255 ) );
			
		}
	}



	if ( Debugging::ReturnMod ( ) ) {
		float size=SIZE;
		if ( type != 0 ) {
			if ( PlayerBullet ) { //플레이어가 쏜 총알
				if ( type != 100 && type != 200 ) {
					size = 4 * SIZE;

				}
				else if ( type == 100 ) { //연막
					size = 4 * SIZE + counter;
					//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );


				}
				else { //대쉬
					size = 128;

					//BLENDFUNCTION bf;
					//bf.BlendOp = AC_SRC_OVER;
					//bf.BlendFlags = 0;
					//bf.AlphaFormat = 0;
					//bf.SourceConstantAlpha = 200 - counter * 15;

					//BitBlt ( dc , 0 , 0 , 128 , 128 , dc , x , y , SRCCOPY );
					//TransparentBlt ( dc , 0 , 0 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_car" ) , 1 * 128 , mx * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );
					//TransparentBlt ( dc , 0 , -10 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_Tank_head" ) , 1 * 128 , my * 128 , 128 , 128 , RGB ( 255 , 255 , 255 ) );

					//AlphaBlend ( dc , x , y , 128 , 128 , dc , 0 , 0 , 128 , 128 , bf );
					//TransparentBlt ( dc , 0 , 0 , 128 , 128 , Texture::getInstance ( ).Texture_GetDC ( "B_STAGE_2" ) , 0 / 2 , 0 / 2 , 128 / 2 , 128 / 2 , RGB ( 255 , 255 , 255 ) );

				}
				//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
			}
			else {  // 몬스터가 쏜 총알
				if ( type == 14 ) { // 자폭이 폭발
					size = SIZE + counter;

					//Ellipse ( dc , x - SIZE - counter , y - SIZE - counter , x + SIZE + counter , y + SIZE + counter );
				}
				else { //오줌이
					size = 4 * SIZE;

				}

			}
		}
		else {
			if ( PlayerBullet ) {
				size = 4 * SIZE;

			}
		}
		
		Rectangle ( dc , x - size , y - size , x + size , y + size );



		

	}

}

void bullet::Update ( ) {
	move ( );

}

void BulletManager::CreateBullet (bullet*& newbullet ) {

		bullets.push_back ( newbullet );
	
}

void BulletManager::DeleteBullet() {
	if ( bullets.size()  ) {
		 deletetime += Time::DeltaTime ( );
		if ( deletetime > 3.0 ) {
			

				for ( auto iter = bullets.begin ( ); iter != bullets.end ( );) {
					if ( ( *iter )->return_type ( ) == 0 && ( *iter )->return_frame ( ) >6 ) {  // 반복자가 가리키는 객체에 접근하기 위해 *iter 사용
						bullet* del = *iter;  // 삭제할 노드의 포인터를 저장
						iter = bullets.erase ( iter );  // 삭제한 노드의 다음 노드의 반복자를 반환
					
						delete del;  // 삭제할 노드를 메모리에서 해제

						std::cout << "aa" << std::endl;
					}
					else {
						++iter;  // 다음 노드로 이동
					}
				}
				deletetime = 0;
		}
		

	}
	

}

void BulletManager::Update() {
	for ( auto& iter : bullets) {
		iter->Update ( );
	}
	DeleteBullet ( );
	
}


void BulletManager::Render( const HDC& dc) {
	HBRUSH oldBrush=0;

	if ( Debugging::ReturnMod ( ) ) {
		
		oldBrush=(HBRUSH)SelectObject ( dc ,Debugging::NULLBRUSH );

	}

	for ( auto& iter : bullets ) {
		
			iter->Render ( dc );
		
	}

	if ( Debugging::ReturnMod ( ) ) {
		SelectObject ( dc,oldBrush );

	}
	
}


