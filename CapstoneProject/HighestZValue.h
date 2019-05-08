#pragma once
#include "ScenarioMetric.h"
class HighestZValue : public ScenarioMetric
{
public:
	HighestZValue(VAST *VASTObject);
	~HighestZValue();
	double value;
};

