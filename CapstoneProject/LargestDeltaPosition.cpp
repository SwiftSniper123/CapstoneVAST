#include "LargestDeltaPosition.h"



LargestDeltaPosition::LargestDeltaPosition(AV* _av, Environment *_env) : ScenarioMetric ("LargestDeltaPosition",_av, _env)
{
	value = 0;
	prevPosition = {};
}


LargestDeltaPosition::~LargestDeltaPosition()
{
}

void LargestDeltaPosition::calculate()
{
	if (initial)
	{
		prevPosition.x = av->position.x;
		prevPosition.y = av->position.y;
		prevPosition.z = av->position.z;
		initial = false;
	}
	else
	{
		double xDif = av->position.x - prevPosition.x;
		double yDif = av->position.y - prevPosition.y;
		double zDif = av->position.z - prevPosition.z;
		double temp = sqrt((xDif*xDif) + (yDif*yDif) + (zDif*zDif));

		if (temp > value)
			value = temp;

	}
}
