#include"MATH.h"

float length(int x1, int y1, int x2, int y2) {
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double angle(double x1, double y1, double x2, double y2) {
	return atan2(y1-y2,x1-x2);
}

bool IntersectRect_float(RECTS& rect1, RECTS& rect2){
	// rect1이 rect2의 오른쪽에 있는지 확인
	if (rect1.right < rect2.left)
		return false;

	// rect1이 rect2의 왼쪽에 있는지 확인
	if (rect1.left > rect2.right)
		return false;

	// rect1이 rect2의 아래에 있는지 확인
	if (rect1.bottom < rect2.top)
		return false;

	// rect1이 rect2의 위에 있는지 확인
	if (rect1.top > rect2.bottom)
		return false;

	// 위의 모든 조건을 만족하지 않으면 두 사각형이 겹침
	return true;


}


bool PtinRect_float(const RECTS& rect, const POINT& point) {
	return (rect.left<point.x && rect.right>point.x && rect.bottom > point.y && rect.top < point.y);

}

RECTS float_return(const int& left, const int& top, const int& right, const int& bottom) {
	RECTS return_rects = { static_cast<float> (left), static_cast<float> (top), static_cast<float>(right), static_cast<float>(bottom) };
	return return_rects;
}

