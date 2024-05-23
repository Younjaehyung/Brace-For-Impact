#include "BULLET.h"
#include "MATH.h"
#include <random>

bulletmanager::bulletmanager() {

}
void bulletmanager::move(bullet*& hd) {
	for (bullet* p = hd; p != NULL; p = p->next) {
		p->x += p->mx;
		p->y += p->my;

		if (p->x < 0|| p->y<0 ) {
			p->type = 0;
		}

	}
}

void bulletmanager::deleteBullet(bullet*& hd) {
	if (hd != NULL) {
		bullet* temp1 = hd;
		bullet* temp2 = hd;
		while (1) {
			if (hd->type == 0) {
				hd = hd->next;
				delete temp1;
				temp1 = hd;
				temp2 = hd;
			}
			else {
				temp1 = temp1->next;
				if (temp1 == NULL) {
					break;
				}
				if (temp1->type == 0) {
					temp2->next = temp1->next;
					delete temp1;
					temp1 = temp2;
				}
				else {
					temp2 = temp1;
				}
			}
		}
	}

}

void bulletmanager::f_Updte(bullet*& hd) {
	move(hd);
	//deleteBullet(hd);
}


void bulletmanager::rander(HDC dc,bullet*& hd) {
	for (bullet* p = hd; p != NULL; p = p->next) {
		Ellipse(dc, p->x - 5, p->y - 5, p->x + 5, p->y + 5);
	}
}


