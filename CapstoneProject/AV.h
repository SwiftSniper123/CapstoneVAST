#pragma once
#include "Sensor.h"
#include <vector>
#include "vector3.h"

class AV
{
public:
	AV(vector3 _position, vector3 _bounds, vector3 _rotation)
	{
		position = _position;
		bounds = _bounds;
		rotation = _rotation;
	}
	~AV();
	void update(vector3 _position, vector3 _rotation)
	{
		position = _position;
		rotation = _rotation;
	}
	std::vector<Sensor> sensors;
	vector3 position;
	vector3 bounds;
	vector3 rotation;
};

