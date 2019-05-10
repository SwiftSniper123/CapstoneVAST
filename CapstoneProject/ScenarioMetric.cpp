#include "ScenarioMetric.h"



ScenarioMetric::ScenarioMetric()
{
}

ScenarioMetric::ScenarioMetric(string _name, AV *_av, Environment *_env)
{
	name = _name;
	av = _av;
	env = _env;
}

ScenarioMetric::~ScenarioMetric()
{
}