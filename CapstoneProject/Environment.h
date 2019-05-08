#pragma once
#include "Obstacle.h"
#include <vector>
#include "vector3.h"

class Environment
{
public:
	Environment();
	Environment(vector3 _bounds)
	{
		bounds = _bounds;
	}
	~Environment();
	std::vector<Obstacle> staticObstacles;
	std::vector<Obstacle> dynamicObstacles;
	vector3 bounds;
};

