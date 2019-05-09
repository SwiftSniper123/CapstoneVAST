#pragma once
#include "Obstacle.h"
#include <vector>
#include "vector3.h"
#include "AV.h"

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

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void addAV(AV *AV) = 0;
	virtual void Connect() {};
	virtual void Close() = 0;

	std::vector<Obstacle> staticObstacles;
	std::vector<Obstacle> dynamicObstacles;

	string configFileLocation;
	string exeLocation;
	int port;
	vector3 bounds;
};

