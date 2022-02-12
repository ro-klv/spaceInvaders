#pragma once
#include "CollidableGameObject.h"



class Player : public CollidableGameObject {
	float speed = 10.0f;
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT;
	int lives = 3;
	int wins = 0;
	int t = 0;
	bool dead = false;
	graphics::Brush br;



public:
	void draw() override;
	void update() override;

	void setPosX(const float& x) ;
	void setPosY(const float& y) ;

	float getPosX();
	float getPosY();

	void setLives(const float& l);
	int getLives();

	void  setT(int& t);
	void setDead(bool d);
	bool getDead();
	void setWins(const int& w);
	int getWins();



	Disk getCollisionHull() override;

	
	

};