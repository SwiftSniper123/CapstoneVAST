#pragma once
#include "ScenarioMetric.h"
#include "vector3.h"

class LargestDeltaPosition :
	public ScenarioMetric
{
public:
	LargestDeltaPosition(AV* _av, Environment *_env);
	~LargestDeltaPosition();
	/*inherited function*/
	void calculate();
	
private:
	vector3 prevPosition;
	bool initial = true;
};

