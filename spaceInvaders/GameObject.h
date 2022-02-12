#pragma once
#include "graphics.h"
#include "Config.h"

class GameObject {

public:

	virtual void draw() = 0;
	virtual void update() = 0;

	virtual ~GameObject(){}
};