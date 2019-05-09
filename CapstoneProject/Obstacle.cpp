#include "Obstacle.h"



Obstacle::Obstacle()
{
}

Obstacle::Obstacle(std::string name, vector3 position, vector3 bounds, vector3 rotation)
{
	_name = name;
	_position.x = position.x;
	_position.y = position.y;
	_position.z = position.z;
	_bounds = bounds;
	_rotation = rotation;
}


Obstacle::~Obstacle()
{
}
