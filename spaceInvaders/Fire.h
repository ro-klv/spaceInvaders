#pragma once
#include "CollidableGameObject.h"



class Fire : public CollidableGameObject {
	float speed = 5.0f;
	float pos_x;
	float pos_y;

public:
	void draw() override;
	void update() override;

	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }

	Disk getCollisionHull() override;

	Fire(float x, float y) : pos_x(x), pos_y(y) {}



};