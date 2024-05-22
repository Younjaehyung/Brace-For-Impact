#pragma once
#include <windows.h>
#include "Player1.h"


struct bullet{
	int x;
	int y;
	int mx;
	int my;
	int type;
	bullet* next;
};


