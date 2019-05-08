#include "HighestXValue.h"



HighestXValue::HighestXValue(VAST *VASTObject) : ScenarioMetric(VASTObject)
{
	//get number of AVs
	numAVs = _VASTObject->AVs.size();
	value = -1.0*INFINITY;
}


HighestXValue::~HighestXValue()
{
	for (int n = 0; n < numAVs; n++)
	{
		if (_VASTObject->AVs[n]->position.x > value)
			value = _VASTObject->AVs[n]->position.x;
	}
}
