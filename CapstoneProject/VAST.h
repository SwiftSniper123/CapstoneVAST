#pragma once
#include "AV.h"
#include "Environment.h"
#include "VASTConstants.h"
#include "VType.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

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

	string RunDataFileName = "RunData.csv";
	string AVIDsFileName = "AVIDs.csv";
	string CollisionsFileName = "Collisions.csv";
	string MetricsFileName = "Metrics.csv";
	string ColDetInputFileName = "ColDetInput.csv";

	std::ofstream RunData;
	std::ofstream AVIDs;
	std::ofstream Collisions;
	std::ofstream Metrics;
	std::ofstream ColDetInput;
};

