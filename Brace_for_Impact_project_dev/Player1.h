#pragma once
#include <Windows.h>
#include "input.h"
#include "Time.h"
#include "MATH.h"


class Player1
{

private:
	RECTS rect;
	int count = 0;
	

public:
	Player1();
	void f_Render(HDC mDC);
	void f_Update();
	void f_FixedUpdate();
	RECTS f_ReturnRect();
};

class Player2
{

private:
	RECTS rect;
	int count = 0;


public:
	Player2();
	void f_Render(HDC mDC);
	void f_Update();
	void f_FixedUpdate();
	RECTS f_ReturnRect();
};

