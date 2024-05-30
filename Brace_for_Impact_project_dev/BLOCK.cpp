#include"BLOCK.h"

Block::Block ( ) {
	rect.left = 400;
	rect.right = 800;
	rect.top = 400;
	rect.bottom = 450;
	type = 3;
}


void Block::Render ( HDC dc ) {
	Rectangle ( dc , rect.left , rect.top , rect.right , rect.bottom );
}

RECTS Block::ReturnRect ( ) {
	return rect;
}