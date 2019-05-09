#pragma once

#include "TraCIAPI.h"
#include <Windows.h>
#include <cstdlib>

#include "Environment.h"
#include "VAST.h"

using std::string;

class SumoEnvironment : public Environment
{
public:
	SumoEnvironment() {};
	SumoEnvironment(string _configFileLocation, string _SUMOexeLocation, int _port, vector3 _bounds, dataMap _envMap);

	dataMap envMap;

	//Opens the Sumo Environment with the file location
	void Initialize();

	void Update();

	void Connect();

	void Close();

	//Gets the information from Sumo via traci commands
	void getMapInformation();

	//sends the new command to the AV in sumo if this is required
	void changeAVCommand();

	//called by the update function to run all of the functions of the child classes
	//virtual dataMap callUpdateFunctions();

	void stopReplication(bool another, string runID);

	void setSeed(string _seed);

	void addAV(AV *_AV);

private:
	
	vector<AV*> AVs;
	TraCIAPI traci;
	dataMap currentData;
	dataMap runData;
	dataMap configData;
	string seed = "r";

	LPSTR cmdArgs;
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
};