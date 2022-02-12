#pragma once
#include "Alien.h"

void Alien::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + name;
	graphics::setOrientation(rotation);
	graphics::drawRect(pos_x, pos_y, 60, 60, br);
	graphics::resetPose();

}

void Alien::update()
{


	if (x <= 10)
	{
		name = "alien.png";
		rotation = -30.0f;

	}
	else
	{
		name = "alien2.png";
		rotation = 0.0f;
	}

	x++;
	if (x == 20) { x = 0; }




	
}



void Alien::setPosX(const float& x) {
	pos_x = x;
}

void Alien::setPosY(const float& y) {
	pos_y = y;
}

float Alien::getPosX()
{
	return pos_x;
}

float Alien::getPosY()
{
	return pos_y;
}

void Alien::setLeft(bool l) {
	left = l;
}



bool Alien::getLeft() {
	return left;
}



Disk Alien::getCollisionHull() {

	Disk disk;
	disk.x = pos_x;
	disk.y = pos_y;
	disk.r = 50.0f;
	return disk;
}



