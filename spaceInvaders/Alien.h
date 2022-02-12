#pragma once
#include "CollidableGameObject.h"


class Alien : public CollidableGameObject {

	float pos_x;
	float pos_y;
	float rotation = 0.0f;
	bool left = false;


	std::string name = "alien.png";
	int x = 0;



public:
	void draw() override;
	void update() override;


	void setPosX(const float& x);
	void setPosY(const float& y);

	float getPosX();
	float getPosY();


	Disk getCollisionHull() override;

	void setLeft(bool l);
	bool getLeft() ;





	Alien(float x, float y) : pos_x(x), pos_y(y) {}

};