#include "bullet.hh"

bullet::bullet(int key, int x, int y) : sprite("assets/bullet.png") {

	this->direction = key;
	this->x = x;
	this->y = y;

}

void bullet::update(float delta) {

	switch (direction) {
	case 0: {	//LEFT
		this->x -= 300 * delta;
	} break;
	case 1: {
		this->x -= 200 * delta;
		this->y -= 200 * delta;
	} break;
	case 2: {
		this->y -= 300 * delta;
	} break;
	case 3: {
		this->y -= 200 * delta;
		this->x += 200 * delta;
	} break;
	case 4: {
		this->x += 300 * delta;
	} break;
	case 5: {
		this->x += 200 * delta;
		this->y += 200 * delta;
	} break;
	case 6: {
		this->y += 300 * delta;
	} break;
	case 7: {
		this->y += 200 * delta;
		this->x -= 200 * delta;
	} break;
	}

	// update enemy collision rect
	setCollisionRect(20, 20);

}