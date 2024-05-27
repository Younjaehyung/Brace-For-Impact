#pragma once
#include<math.h>
#include<Windows.h>
#define PI 3.14
//두 점의 길이
float length(int x1, int y1, int x2, int y2);
//두 점의 각도
double angle(double x1, double y1, double x2, double y2);
//두 점의 직선의 방정식 f(x)=y
float a2bLine(float x, float p1x, float p1y, float mopx, float mopy);

typedef struct RECTS {
	float left;
	float top;
	float right;
	float bottom;
}RECTS;

bool IntersectRect_float(RECTS& ,RECTS&);


bool PtinRect_float(const RECTS& rect, const POINT& point);


RECTS float_return(const int& left, const int& top, const int& right, const int& bottom);
