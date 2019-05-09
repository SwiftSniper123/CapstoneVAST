#pragma once
#include "Sensor.h"
#include <vector>
#include "vector3.h"
#include <string>
#include "VType.h"
#include <map>
#include "ScenarioMetric.h"

typedef std::map<string, VType*> dataMap;

class AV
{
public:
	AV();
	AV(string _name, vector3 _position, vector3 _bounds, vector3 _rotation, int _port, string _exe)
	{
		name = _name;
		position = _position;
		bounds = _bounds;
		rotation = _rotation;
		port = _port;
		exe = _exe;
	}
	~AV();
	
	virtual void Initialize() = 0;
	virtual void Update() = 0;

	std::vector<Sensor> sensors;
	std::vector<ScenarioMetric*> metrics;
	string name;
	vector3 position;
	vector3 bounds;
	vector3 rotation;
	int port;
	string exe;
	void runScript();

private:

};

