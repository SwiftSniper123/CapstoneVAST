#pragma once
#include "VAST.h"

class ScenarioMetric
{
public:
	ScenarioMetric(VAST *VASTObject);
	~ScenarioMetric();
	virtual void calculate() = 0;
	int numAVs;
	VAST *_VASTObject;
};
