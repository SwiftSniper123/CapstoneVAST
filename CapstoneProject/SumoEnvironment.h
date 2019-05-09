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
	SumoEnvironment(string _configFileLocation, string _SUMOexeLocation, int _port, vector3 _bounds, dataMap _envMap) : Environment(_configFileLocation, _SUMOexeLocation, _port, _bounds)
	{
		envMap = _envMap;
	}

	dataMap envMap;

	//Opens the Sumo Environment with the file location
	void openEnvironment();

	//Gets the information from Sumo via traci commands
	void getMapInformation();

	//sends the new command to the AV in sumo if this is required
	void changeAVCommand();

	//called by the update function to run all of the functions of the child classes
	virtual dataMap callUpdateFunctions();

	void stopReplication(bool another, string runID);

	void setSeed(string seed);

	void addAV(AV *AV);

private:
	string fileLocation;
	int random; //Replace with function for setting the seed?
	string seed;
	string SUMOexeLocation;
	Integer port;
	vector<string> AVid;
	TraCIAPI traci;
	dataMap currentData;
	dataMap runData;
	dataMap configData;
	vector3 bounds;

	LPWSTR cmdArgs;
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
};