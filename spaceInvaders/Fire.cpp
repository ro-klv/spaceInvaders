#pragma once

#include "Fire.h"


void Fire::draw()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = std::string(ASSET_PATH) + "fire.png";
	graphics::drawRect(pos_x, pos_y, 5, 30, br);

}



void Fire::update()
{
	pos_y -= speed * graphics::getDeltaTime() / 8.0f;
}




Disk Fire::getCollisionHull() {

	Disk disk;
	disk.x = pos_x;
	disk.y = pos_y;
	disk.r = 10.0f;
	return disk;
}


