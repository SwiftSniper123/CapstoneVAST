#pragma once
#include "ScenarioMetric.h"

class AverageAcceleration : public ScenarioMetric
{
public:
	AverageAcceleration();
	~AverageAcceleration();

	/*inherited function*/
	void calculate();
private:
	double value;
	int numDataPoints;
};

