#pragma once
#include "GameObject.h"



class Explosion : public GameObject {

	float pos_x;
	float pos_y;
	int t = 0;


public:
	void draw() override;
	void update() override;

	int getT(){ return t; }

	Explosion(float x, float y) : pos_x(x), pos_y(y) {}



};