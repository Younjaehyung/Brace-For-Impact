#include "BULLET.h"
#include "MATH.h"
#include <random>

bulletmanager::bulletmanager() {

}
void bulletmanager::move(bullet*& hd) {
	for (bullet* p = hd; p != NULL; p = p->next) {
		p->x += p->mx;
		p->y += p->my;
	}
}
void bulletmanager::rander(HDC dc,bullet*& hd) {
	for (bullet* p = hd; p != NULL; p = p->next) {
		Ellipse(dc, p->x - 5, p->y - 5, p->x + 5, p->y + 5);
	}
}
