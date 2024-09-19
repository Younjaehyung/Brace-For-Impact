#pragma once
#include<math.h>
#include<Windows.h>
#include"BULLET.h"
#define PI 3.14

float abs_F ( float i );

float length(int x1, int y1, int x2, int y2);

double angle(double x1, double y1, double x2, double y2);

void bulletshot ( float x1 , float y1 , float x2 , float y2 , int type );

bool ck8 ( int map[ 32 ][ 32 ] , int x , int y , int ck );
int ck8_move ( int map[ 32 ][ 32 ] , int x , int y , int ck );

typedef struct RECTS {
	float left;
	float top;
	float right;
	float bottom;
}RECTS;

float middleX ( RECTS a );
float middleY ( RECTS a );

float a2bLine ( float x , float p1x , float p1y , float mopx , float mopy );

BOOL inrect ( RECTS r , float x , float y );
BOOL inrect_f ( float left , float top , float right, float bottom , float x , float y );

BOOL rect2Cir ( RECTS rect , double& x , double& y , int sz );

BOOL rect2Line ( RECTS rect , float& p1x , float& p1y , float& mopx , float& mopy );
BOOL rect2Line4 ( RECTS rect , RECTS p1 , RECTS mop );

BOOL rect2rect ( RECTS block , RECTS mop );
BOOL rect2rect_f ( float left , float top , float right , float bottom , RECTS mop );

BOOL ckMopDown ( RECTS rect , RECTS mop );
BOOL ckMopUp ( RECTS rect , RECTS mop );
BOOL ckMopLeft ( RECTS rect , RECTS mop );
BOOL ckMopRight ( RECTS rect , RECTS mop );

bool IntersectRect_float(RECTS& ,RECTS&);


bool PtinRect_float(const RECTS& rect, const POINT& point);


RECTS float_return(const int& left, const int& top, const int& right, const int& bottom);

double Radian_return ( float& angle );