#pragma once
#include "Player.h"
#include "graphics.h"




void Player::draw()
{

	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "ship.png";
	graphics::drawRect(pos_x, pos_y, 50, 50, br);
	graphics::resetPose();


}

void Player::update()
{

		if (dead) {

			if (t < 40) {
				br.fill_opacity = 0.0f;
			}
			else {
				br.fill_opacity = 1.0f;
				t = 0;
				dead = false;
			}
			t++;
		}
		else {

			if (graphics::getKeyState(graphics::SCANCODE_UP))
			{
				pos_y -= speed * graphics::getDeltaTime() / 10.0f;
			}
			if (graphics::getKeyState(graphics::SCANCODE_DOWN))
			{
				pos_y += speed * graphics::getDeltaTime() / 10.0f;
			}
			if (graphics::getKeyState(graphics::SCANCODE_LEFT))
			{
				pos_x -= speed * graphics::getDeltaTime() / 30.0f;
			}
			if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
			{
				pos_x += speed * graphics::getDeltaTime() / 30.0f;
			}


			if (pos_x < 50) pos_x = 50;
			if (pos_x > CANVAS_WIDTH - 50) pos_x = CANVAS_WIDTH - 50;
			if (pos_y < 50) pos_y = 50;
			if (pos_y > CANVAS_HEIGHT - 50) pos_y = CANVAS_HEIGHT - 50;


		}

	
}



Disk Player::getCollisionHull() {

	Disk disk;
	disk.x = pos_x;
	disk.y = pos_y;
	disk.r = 25.0f;
	return disk;
}


void  Player::setPosX(const float& x) {
	pos_x = x;
}
void  Player::setPosY(const float& y) {
	pos_y = y;
}

float Player::getPosX()
{
	return pos_x;
}

float Player::getPosY()
{
	return pos_y;
}

void Player::setLives(const float& l)
{
	lives = l;
}

int Player::getLives()
{
	return lives;
}

void Player::setT(int& t)
{
	t = t;
}

void Player::setDead(bool d)
{
	dead = d;
}

bool Player::getDead()
{
	return dead;
}

void Player::setWins(const int& w)
{
	wins = w;
}

int Player::getWins()
{
	return wins;
}
