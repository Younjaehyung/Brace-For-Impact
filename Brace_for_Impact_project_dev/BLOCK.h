#pragma once
#include <Windows.h>
#include "input.h"
#include "MATH.h"


class Block
{
private:
	RECTS rect;
	int type;
public:
	Block ( );
	void Render ( const HDC& mDC );
	void makeblock ( RECTS rects , int type );
	RECTS ReturnRect ( );
};

class BlockManager {
private:
	BlockManager ( ) {};
	std::vector<Block> Blocks;

public:
	static BlockManager& getInstance ( ) {
		static BlockManager instance;
		return instance;
	}

	void Initilize ( int type );
	void Update ( );
	void Render ( const HDC& );
	std::vector<Block>& BlockReturn ( );
};
