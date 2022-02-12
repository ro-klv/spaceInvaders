#pragma once

#include "Explosion.h"



void Explosion::draw()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = std::string(ASSET_PATH) + "e.png";
	graphics::drawRect(pos_x, pos_y, 40, 40, br);

}


void Explosion::update()
{
	t++;
}


