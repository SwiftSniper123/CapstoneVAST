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

typedef map<string, VType*> dataMap; // A map of VTypes for use in the Parser
typedef pair<string, VType*> namedData; // A pair to insert into the dataMap

class VAST
{
public:
	VAST();
	~VAST();

	std::vector<AV*> AVs;								// Vector of AVs
	Environment* env;									// Environment representation
	std::vector<std::vector<ScenarioMetric*>> metrics;	// A vector of metrics for each AV

	dataMap _VASTConfigMap;								// Map containing initial VAST configuration settings
	dataMap _EnvConfig;									// Map containing initial Environment Configuration settings
	dataMap _AVConfig;									// Map containing initial AV configuration settings
	vector<dataMap> _AVConfigs;							// Vector of AV configuration settings

	dataMap _AVRun_Data;								// Map of optional AV data input by user
	dataMap _EnvRun_Data;								// Map of optional Environment data input by user

	void Parse(string _file);							// Parses file passed to it and populates the various maps
	void Run();											// Begins the simulation run
	void publishMetrics();								// Publishes metrics to a file post-run

private:
	void fillMap(string currentModule, dataMap &run_Data, string type, string key, string value); // Internal parser function
	double currentSimTime = 0;
	double timeStep;
	int runID = 0;

	// Define locations for output files
	const char *RunDataFileName = "PostSim/RunData.csv";
	string MetricsFileName = "Metrics.csv";
	string AVColDetInitFileName = "CollisionDetection/CollisionDetection_Data/AVColDetInit.csv";
	string AVColDetInfoFileName = "CollisionDetection/CollisionDetection_Data/AVColDetInfo.csv";
	string ObsColDetInfoFileName = "CollisionDetection/CollisionDetection_Data/ObsColDetInfo.csv";
	string CollisionFileName = "CollisionDetection/CollisionDetection_Data/Collisions.csv";

	// Output Data files
	std::ofstream RunData;
	std::ofstream Metrics;
	std::ofstream AVColDetInit;
	std::ofstream AVColDetInfo;
	std::ofstream ObsColDetInfo;

	LPSTR cmdArgs; //for spawning an external process
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
};

