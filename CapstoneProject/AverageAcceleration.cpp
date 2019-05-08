#include "AverageAcceleration.h"



AverageAcceleration::AverageAcceleration()
{
	numDataPoints = 0;
	//get number of AVs
	numAVs = _VASTObject->AVs.size();
}


AverageAcceleration::~AverageAcceleration()
{
}

void AverageAcceleration::calculate()
{
	for (int n = 0; n < numAVs; n++)
	{
		_VASTObject->AVs[n]->
	}
}
