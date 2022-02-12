#include "Game.h"


void Game::draw()
{
	if (st == start) {
		drawStart();
	}
	else if (st == play) {
		drawPlay();
	}
	else  if (st == pause) {
		drawPause();
	}
	else  if (st == win) {
		drawWin();
	}
	else if (st == gameOver) {
		drawGameOver();
	}

}

void Game::update()
{



	if (st == start) {
		updateStart();
	}
	else if (st == play) {

		updatePlay();
	}
	else  if (st == pause) {
		updatePause();
	}
	else  if (st == win) {
		updateWin();
	}
	else if (st == gameOver) {
		updateGameOver();
	}



}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "FFF Tusj.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "horror-atmosphere-background.mp3", 0.9f, true, 4000);

}

void Game::drawStart()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "galaxy.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, y, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawText(250, 250, 50, "Press ENTER to start ", br);
	drawText(250, 300, 50, "Press ESC to exit", br);
}

void Game::drawPlay()
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "glx.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, y, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::drawRect(x, y - CANVAS_HEIGHT, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	graphics::resetPose();

	if (ship) {
		ship->draw();
		char l[10];
		sprintf_s(l, "lives : %d", ship->getLives());
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.5f;
		br.fill_color[2] = 0.0f;
		graphics::drawText(50, 35, 35, l, br);
	}


	if (!aliens.empty())
		for (Alien* a : aliens)
		{
			if (a) {
				a->draw();

			}
		}


	if (!fire_list.empty())
		for (Fire* f : fire_list)
		{
			if (f)
				f->draw();
		}


	if (explode) {
		explode->draw();
	}


	char s[20];
	sprintf_s(s, "score : %d", score);
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
	graphics::drawText(700, 35, 35, s, br);



	char p[20];
	sprintf_s(p, "Press TAB to PAUSE");
	br.fill_color[0] = 0.9f;
	br.fill_color[1] = 0.9f;
	br.fill_color[2] = 0.0f;
	graphics::drawText(350, 35, 20, p, br);






}

void Game::updateStart()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		st = play;
		graphics::playMusic(std::string(ASSET_PATH) + "Komiku_-_15_-_You_cant_beat_the_machine.mp3", 0.2f, true, 2000);
	}

}

void Game::updatePlay()
{

	//---------------- BACKGROUND----------------------------

	if (y - CANVAS_HEIGHT > CANVAS_HEIGHT / 2)
		y = CANVAS_HEIGHT / 2;

	y += CANVAS_HEIGHT * graphics::getDeltaTime() / 5000.0f / 4;

	//-------------------PAUSE---------------------------------
	if (graphics::getKeyState(graphics::SCANCODE_TAB)) {
		st = pause;
		graphics::playMusic(std::string(ASSET_PATH) + "horror-atmosphere-background.mp3", 0.9f, true, 4000);
	}


	//--------------------PLAYER------------------------------

	if (!ship_init)
	{
		ship = new Player();
		ship_init = true;

	}
	if (ship)
	{
		ship->update();

		//-----------------SHOOT----------------------------

		if (!ship->getDead() && graphics::getKeyState(graphics::SCANCODE_SPACE) && !pressed) {

			Fire* fire = new Fire(ship->getPosX(), ship->getPosY());
			fire_list.push_front(fire);
			graphics::playSound(std::string(ASSET_PATH) + "shoot2.wav", 0.9f, false);
			pressed = true;

		}

		if (!graphics::getKeyState(graphics::SCANCODE_SPACE))
			pressed = false;



	}


	// ------------------ENEMY----------------------


	createAliens();


	updateAliens(s);

	if (!aliens.empty())
		collisionEnemyFire();

	if (!aliens.empty())
		collisionEnemyPlayer();



	//fire out of canvas 

	for (auto f = fire_list.begin(); f != fire_list.end();)
	{
		Fire* fr = *f;

		if (fr->getPosY() < 0) {
			f = fire_list.erase(f);
			delete fr;
			fr = nullptr;
		}
		else f++;

	}




	if (!fire_list.empty())
		for (Fire* f : fire_list)
		{
			if (f) {
				f->update();
			}
		}


	//----------------EXPLOSION-----------------------

	if (explode) {

		explode->update();
		if (explode->getT() == 3) {
			delete explode;
			explode = nullptr;

		}
	}


}


//------------------- DRAW PAUSE -----------------------------
void Game::drawPause()
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "galaxy.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawText(250, 200, 70, "Game PAUSED !", br);
	drawText(250, 300, 40, "Press ENTER to continue !", br);
	drawText(250, 400, 30, "Press ESC to exit!", br);

}

//------------------ UPDATE PAUSE ----------------------------
void Game::updatePause()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		st = play;
		graphics::playMusic(std::string(ASSET_PATH) + "Komiku_-_15_-_You_cant_beat_the_machine.mp3", 0.2f, true, 2000);
	}

}

//------------------- DRAW WIN -------------------------------
void Game::drawWin()
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "galaxy.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawText(300, 150, 70, "Gongrats  ", br);
	drawText(200, 250, 70, "You are the best", br);
	drawText(250, 350, 30, "Press ENTER to play again", br);
	drawText(250, 400, 30, "Press ESC to exit!", br);
}
//------------------ UPDATE WIN ------------------------------
void Game::updateWin()
{

	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		st = play;
		graphics::playMusic(std::string(ASSET_PATH) + "Komiku_-_15_-_You_cant_beat_the_machine.mp3", 0.2f, true, 2000);
	}

	deleteFire();
	//delete explosions
	if (explode) {
		delete explode;
		explode = nullptr;
	}

	ship->setLives(3);
	score = 0;
	s = 4;
	ship->setWins(0);
}






void Game::drawGameOver()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "galaxy.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	drawText(250, 200, 70, "GAME OVER ", br);
	drawText(250, 300, 40, "Press ENTER to play again ", br);
	drawText(250, 400, 30, "Press ESC to exit", br);
}

void Game::updateGameOver()
{


	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		st = play;
		graphics::playMusic(std::string(ASSET_PATH) + "Komiku_-_15_-_You_cant_beat_the_machine.mp3", 0.2f, true, 2000);

	}
	deleteAliens();
	deleteFire();

	//--------------delete explosions--------------------------
	if (explode) {
		delete explode;
		explode = nullptr;
	}

	score = 0;
	s = 4;

}

void Game::deleteFire() {

	for (Fire*& f : fire_list)
	{
		delete f;
	}
	fire_list.clear();
}


void Game::createAliens() {
	if (aliens.empty())
	{
		float x, y;
		int h = 0;
		aliens.resize(20);
		for (int i = 0; i < 20; i++) {

			if (i < 5) {

				y = CANVAS_HEIGHT / 8;
				h = i;
			}

			else if (i < 10) {
				y = CANVAS_HEIGHT / 8 + 50;
				h = i - 5;
			}

			else if (i < 15) {
				h = i - 10;
				y = CANVAS_HEIGHT / 8 + 100;
			}
			else {
				h = i - 15;
				y = CANVAS_HEIGHT / 8 + 150;

			}

			x = CANVAS_WIDTH / 3 + h * 100;


			Alien* alien = new Alien(x, y);
			aliens[i] = alien;
		}
	}

}

void Game::updateAliens(int s) {

	float h = 500 * graphics::getDeltaTime() / 1200.0f / s;
	int i = 0;
	int l = 50;
	int r = 900;

	if (!aliens.empty()) {
		for (Alien*&a : aliens)
		{

			if (i % 5 == 0) {
				l = 100;
				r = 500;
			}
			if (i % 5 == 1) {
				l = 200;
				r = 600;
			}
			if (i % 5 == 2) {
				l = 300;
				r = 700;
			}
			if (i % 5 == 3) {
				l = 400;
				r = 800;
			}
			if (i % 5 == 4) {
				l = 500;
				r = 900;
			}

			if (a) {

				if (a->getPosX() < l && !a->getLeft()) {
					a->setLeft(true);
					a->setPosX(l);

				}

				if (a->getPosX() > r) {
					a->setLeft(false);
				}

				if (a->getLeft())
					a->setPosX(a->getPosX() + h);
				else
					a->setPosX(a->getPosX() - h);

				a->setPosY(a->getPosY() + 30 * graphics::getDeltaTime() / 1000.0f / s);

				a->update();

				if (a->getPosY() > CANVAS_HEIGHT) {
					delete a;
					a = nullptr;
				}
			}
			i++;
		}


		clearAliens();
	}

}



bool Game::clearAliens() {

	bool clear = true;

	for (Alien*& a : aliens) {
		if (a)
			clear = false;
	}

	if (clear)
		aliens.clear();

	return clear;
}




void Game::deleteAliens() {

	for (Alien*& a : aliens) {

		delete a;
		a = nullptr;
	}

	aliens.clear();
}

bool Game::checkCollision(CollidableGameObject* a, CollidableGameObject* b) {


	if (!a || !b)
	{
		return false;
	}
	else {
		Disk d1 = a->getCollisionHull();
		Disk d2 = b->getCollisionHull();

		float dx = d1.x - d2.x;
		float dy = d1.y - d2.y;

		if (sqrt(dx * dx + dy * dy) < d2.r + d2.r) {

			return true;
		}

	}

}

void Game::collisionEnemyFire() {


	for (auto f = fire_list.begin(); f != fire_list.end();)
	{
		Fire* fr = *f;

		for (Alien*& a : aliens)
		{

			if (a) {

				if (checkCollision(a, fr)) {
					graphics::playSound(std::string(ASSET_PATH) + "4.wav", 0.8f, false);

					score += 500;

					explode = new Explosion(a->getPosX(), a->getPosY());


					delete a;
					a = nullptr;

					f = fire_list.erase(f);
					delete fr;
					fr = nullptr;
				}
			}
		}
		if (f != fire_list.end())
			f++;
	}



	bool clear = clearAliens();

	if (clear) {

		ship->setWins(ship->getWins() + 1);
		if (ship->getWins() > 0 && ship->getWins() <= 3)
			s--;

		if (ship->getWins() == 3)
			st = win;
	}

}

void Game::collisionEnemyPlayer() {

	for (Alien*& a : aliens)
	{
		if (a && ship) {
			if (checkCollision(a, ship)) {

				ship->setLives(ship->getLives() - 1);
				explode = new Explosion(a->getPosX(), a->getPosY());


				graphics::playSound(std::string(ASSET_PATH) + "4.wav", 0.8f, false);

				if (ship->getLives() == 0) {
					delete ship;
					ship = nullptr;
					ship_init = false;

					st = gameOver;
					graphics::playMusic(std::string(ASSET_PATH) + "horror-atmosphere-background.mp3", 0.9f, true, 4000);
				}

				else {

					ship->setDead(true);

					ship->setPosX(CANVAS_WIDTH / 2);
					ship->setPosY(CANVAS_HEIGHT);

				}

				delete a;
				a = nullptr;

			}
		}
	}



}


Game::~Game()
{
	if (ship) {
		delete ship;
		ship = nullptr;
	}

	if (explode) {
		delete explode;
		explode = nullptr;
	}

	deleteFire();
	deleteAliens();

}