#pragma once
#include<math.h>
#include<Windows.h>
#define PI 3.14

float length(int x1, int y1, int x2, int y2);

double angle(double x1, double y1, double x2, double y2);



typedef struct RECTS {
	float left;
	float top;
	float right;
	float bottom;
}RECTS;

float a2bLine ( float x , float p1x , float p1y , float mopx , float mopy );
float a2bLine2 ( float y , float p1x , float p1y , float mopx , float mopy );

BOOL rect2Cir ( RECTS rect , double x , double y , int sz );

BOOL rect2Line ( RECTS rect , float p1x , float p1y , float mopx , float mopy );

bool IntersectRect_float(RECTS& ,RECTS&);


bool PtinRect_float(const RECTS& rect, const POINT& point);


RECTS float_return(const int& left, const int& top, const int& right, const int& bottom);

double Radian_return ( float angle );