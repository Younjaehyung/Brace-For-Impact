#pragma once
#include<math.h>
#include<Windows.h>
#define PI 3.14

float length(int x1, int y1, int x2, int y2);

double angle(int x1, int y1, int x2, int y2);



typedef struct RECTS {
	float left;
	float top;
	float right;
	float bottom;
}RECTS;

bool IntersectRect_float(RECTS& ,RECTS&);


bool PtinRect_float(const RECTS& rect, const POINT& point);


RECTS float_return(const int& left, const int& top, const int& right, const int& bottom);
