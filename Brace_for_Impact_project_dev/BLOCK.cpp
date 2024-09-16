#include"BLOCK.h"

Block::Block ( ) {

	//rect.left < 400 && rect.right > 220) && rect.top < 460 && rect.top > 120
}


void Block::Render ( const HDC& dc ) {
	Rectangle ( dc , rect.left , rect.top , rect.right , rect.bottom );
}

void Block::makeblock (RECTS rects,int type ) {
	if ( type == 1 ) {
		rect = { rects.left * 64 , rects.top * 64 , rects.right * 64 , rects.bottom * 64 };
	}
	else if ( type == 2 ) {
		rect = rects;
	}
	

}


RECTS Block::ReturnRect ( ) {
	return rect;
}

void BlockManager::Initialize ( int type )
{

	Block temp;
	//기본 탱크 내부 포신UI
	temp.makeblock ( { 220,120,400,460 } , 0 );
	Blocks.push_back ( temp );
	if ( type == 1 || type == 2 ) {
		temp.makeblock ( { 0,0,32,6 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,10,3,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,28,32,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 30,0,32,16 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 3,19,8,23 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 6,12,7,13 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 13,10,20,13 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 13,10,20,13 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 13,19,26,23 } , 1 );
		Blocks.push_back ( temp );
	}
	else if ( type == 3 || type == 4 ) {
		temp.makeblock ( { 0,0,8,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 24,0,32,32 } , 1 );
		Blocks.push_back ( temp );
		//temp.makeblock ( { 8,7,11,9 } , 1 );
		//Blocks.push_back ( temp );
		//temp.makeblock ( { 19,12,24,13 } , 1 );
		//Blocks.push_back ( temp );
		//temp.makeblock ( { 8,18,11,20 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,31,32,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,0,32,1 } , 1 );
		Blocks.push_back ( temp );
	}
	else if ( type == 5|| type==6 ) {
		temp.makeblock ( { 0,0,2,7 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 10,0,19,11 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 30,0,32,7 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,14,2,20 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 11,14,19,22 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 30,15,32,20 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 11,27,19,32 } , 1 );
		//장애물 위치 변경
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,30,32,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 0,0,32,1 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { -1,0,0,32 } , 1 );
		Blocks.push_back ( temp );
		temp.makeblock ( { 32,0,33,32 } , 1 );
		Blocks.push_back ( temp );
	}
	
}

void BlockManager::Update ( )
{
}

void BlockManager::Clear ( )
{
	Blocks.clear ( );
}

void BlockManager::Render ( const HDC& dc)
{
	for ( auto& block_render : Blocks ) {
		block_render.Render (dc);
	}

}

std::vector<Block>& BlockManager::BlockReturn ( )
{
	return Blocks;
}
