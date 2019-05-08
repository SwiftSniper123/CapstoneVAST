#include "HighestZValue.h"



HighestZValue::HighestZValue(VAST *VASTObject) : ScenarioMetric(VASTObject)
{
	//get number of AVs
	numAVs = _VASTObject->AVs.size();
	value = -1.0*INFINITY;
}


HighestZValue::~HighestZValue()
{
	for (int n = 0; n < numAVs; n++)
	{
		if (_VASTObject->AVs[n]->position.z > value)
			value = _VASTObject->AVs[n]->position.z;
	}
}
