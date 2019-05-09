#pragma once
#include <string>
#include "AV.h"
#include "Environment.h"

using std::string;

class ScenarioMetric
{
public:
	ScenarioMetric();
	ScenarioMetric(AV *_av, Environment *_env);
	~ScenarioMetric();
	virtual void calculate() = 0;
	int numAVs;
	string name;
	double value;
	AV *av;
	Environment *env;
};
