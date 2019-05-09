#pragma once
#include <string>

using std::string;

class ScenarioMetric
{
public:
	ScenarioMetric();
	~ScenarioMetric();
	virtual void calculate() = 0;
	int numAVs;
	string name;
	double value;
	void Test();
};
