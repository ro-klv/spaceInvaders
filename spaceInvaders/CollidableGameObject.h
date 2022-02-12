#pragma once
#include "util.h"
#include "GameObject.h"

class CollidableGameObject: public GameObject {


public:

	virtual Disk getCollisionHull() = 0;
	virtual ~CollidableGameObject() {}
};