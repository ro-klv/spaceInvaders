#pragma once

#include <list>
#include "Player.h"
#include "Alien.h"
#include "Fire.h"
#include "Explosion.h"
#include <vector>

class Game {

	Player* ship = nullptr;
	bool ship_init = false;


	std::vector<Alien*> aliens;

	std::list<Fire*> fire_list;

	Explosion* explode = nullptr;
	

	bool pressed = false;

	int score = 0;
	int s = 4;

	float x = CANVAS_WIDTH / 2;
	float y = CANVAS_HEIGHT / 2;

	typedef enum  { start, play, pause , win, gameOver } status;
	status st = start;

	void deleteFire();
	void createAliens();
	void updateAliens(int s);
	bool clearAliens();
	void deleteAliens();
	bool checkCollision(CollidableGameObject* a, CollidableGameObject* b);
	void collisionEnemyFire();
	void collisionEnemyPlayer();
	


public:


	void draw();
	void update();
	void init();

	void drawStart();
	void drawPlay();

	void updateStart();
	void updatePlay();

	void drawPause();
	void updatePause();



	void drawWin();
	void updateWin();

	void drawGameOver();
	void updateGameOver();

	~Game();



};