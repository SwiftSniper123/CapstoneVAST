#pragma once
#include "Obstacle.h"
#include <vector>
#include "vector3.h"

using std::string;

class Environment
{
public:
	Environment();
	Environment(string _configFileLocation, string _exeLocation, int _port, vector3 _bounds)
	{
		configFileLocation = _configFileLocation;
		exeLocation = _exeLocation;
		port = _port;
		bounds = _bounds;
	}
	~Environment();
	std::vector<Obstacle> staticObstacles;
	std::vector<Obstacle> dynamicObstacles;

	string configFileLocation;
	string exeLocation;
	int port;
	vector3 bounds;
};

