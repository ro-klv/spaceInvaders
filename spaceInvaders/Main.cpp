#include "graphics.h"
#include "Config.h"
#include "Game.h"

void update(float ms)
{
	Game* pspaceInvaders = reinterpret_cast<Game*> (graphics::getUserData());
	pspaceInvaders->update();	
}


void draw() {
	Game* pspaceInvaders = reinterpret_cast<Game*> (graphics::getUserData());
	pspaceInvaders->draw();
}


int main() {

	

	Game spaceInvaders;

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TNS&RO CREATIONS");
	graphics::setUserData(&spaceInvaders);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);	
	graphics::setCanvasSize(CANVAS_WIDTH,CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	spaceInvaders.init();
	graphics::startMessageLoop();
	

	return 0;
}