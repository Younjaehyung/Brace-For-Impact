#pragma once
#include "Player1.h"
#include "MATH.h"
#include "Resource.h"
class Tank : public Player1
{

private:
	RECTS rect;
	HBITMAP B_Tank_car , B_Tank_head;
public:
	Tank ( );
	void move ( );
	void shooting ( );

	void Init ( HINSTANCE g_hinst );
	void Update ( );
	void render ( HDC , HDC );

};

