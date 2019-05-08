#pragma once
#include "VAST.h"

class ScenarioMetric
{
public:
	ScenarioMetric(VAST *VASTObject)
	{
		_VASTObject = VASTObject;
	}
	~ScenarioMetric();
private:
	VAST *_VASTObject;
};

class ScenarioMetric
{
public:
	ScenarioMetric();
	~ScenarioMetric();
};

