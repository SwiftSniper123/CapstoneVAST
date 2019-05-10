#pragma once
#include "AV.h"
#include "Environment.h"
#include "ScenarioMetric.h"
#include "VASTConstants.h"
#include "VType.h"
#include <Windows.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

using namespace boost::property_tree;
using std::map;
using std::string;
using std::pair;
using std::cout;

typedef map<string, VType*> dataMap;
typedef pair<string, VType*> namedData;

class VAST
{
public:
	VAST();
	VAST(AV* _AVs, Environment* _env);
	~VAST();
	std::vector<AV*> AVs;
	Environment* env;
	std::vector<std::vector<ScenarioMetric*>> metrics;

	dataMap _VASTConfigMap;
	dataMap _EnvConfig;
	dataMap _AVConfig;
	vector<dataMap> _AVConfigs;

	dataMap _AVRun_Data;
	dataMap _EnvRun_Data;

	void Parse(string _file);
	void Run();
	void publishMetrics();

private:
	void fillMap(string currentModule, dataMap &run_Data, string type, string key, string value);
	double currentSimTime = 0;
	double timeStep;

	const char *RunDataFileName = "RunData.csv";
	string MetricsFileName = "Metrics.csv";
	string AVColDetInitFileName = "AVColDetInit.csv";
	string AVColDetInfoFileName = "AVColDetInfo.csv";
	string ObsColDetInfoFileName = "ObsColDetInfo.csv";

	std::ofstream RunData;
	std::ofstream Metrics;
	std::ofstream AVColDetInit;
	std::ofstream AVColDetInfo;
	std::ofstream ObsColDetInfo;

	LPSTR cmdArgs;
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
};

