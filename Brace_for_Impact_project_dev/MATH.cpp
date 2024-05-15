#include"MATH.h"

float length(int x1, int y1, int x2, int y2) {
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double angle(int x1, int y1, int x2, int y2) {
	return atan2(y1-y2,x1-x2 );
}