#include "Obstacle.h"



Obstacle::Obstacle()
{
}

Obstacle::Obstacle(std::string name, vector3 position, vector3 bounds, vector3 rotation)
{
	_name = name;
	_position = position;
	_bounds = bounds;
	_rotation = rotation;
}


Obstacle::~Obstacle()
{
}
