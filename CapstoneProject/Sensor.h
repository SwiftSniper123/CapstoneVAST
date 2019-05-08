#pragma once
#include "vector3.h"

class Sensor
{
public:
	Sensor();
	~Sensor();
	vector3 position;
	vector3 bounds;
	vector3 rotation;
};

