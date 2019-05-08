#pragma once
#include "vector3.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	vector3 position;
	vector3 bounds;
	vector3 rotation;
};

