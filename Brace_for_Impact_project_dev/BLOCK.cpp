#include"BLOCK.h"

Block::Block ( ) {
	rect.left = 64*3;
	rect.right = 64*9;
	rect.top = 64*3;
	rect.bottom = 64*7;
	type = 3;
}


void Block::Render ( const HDC& dc ) {
	Rectangle ( dc , rect.left , rect.top , rect.right , rect.bottom );
}

void Block::makeblock (RECTS rects, int type1 ) {
	rect = rects;
	type = type1;
}


RECTS Block::ReturnRect ( ) {
	return rect;
}

void BlockManager::Initilize ( int type )
{
	Block temp;
	Blocks.push_back (temp);
	RECTS re = {800,200,850,400};
	temp.makeblock ( re , type );
	Blocks.push_back ( temp );

	re = { 200,500,250,700 };
	temp.makeblock ( re , type );
	Blocks.push_back ( temp );
}

void BlockManager::Update ( )
{
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
