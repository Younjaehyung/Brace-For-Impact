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
	void Render ( HDC mDC );
	RECTS ReturnRect ( );
};