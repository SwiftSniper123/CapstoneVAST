#pragma once
#include "vector3.h"
#include <string>

class Obstacle
{
public:
	Obstacle();
	Obstacle(std::string name, vector3 position, vector3 bounds, vector3 rotation);
	~Obstacle();
	vector3 _position;
	vector3 _bounds;
	vector3 _rotation;
	std::string _name;
};

