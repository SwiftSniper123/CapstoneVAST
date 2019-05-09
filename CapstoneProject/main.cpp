#include <iostream>
#include <Windows.h>
#include <string>
#include "VAST.h"

using namespace std;

//AV example
class GroundAV : public AV
{
public:
	GroundAV() {};
	GroundAV(string _name, vector3 _position, vector3 _bounds, vector3 _rotation, int _port, string _exe, dataMap _AVMap) : AV(_name, _position, _bounds, _rotation, _port, _exe) 
	{
		AVMap = _AVMap;
	};

	dataMap AVMap;
};
//Environment example
class UnityEnvironment : public Environment
{
public:
	UnityEnvironment() {};
	UnityEnvironment(string _exeLocation, string _staticObstacleOutput, string _dynamicObstacleRun, string _dynamicObstacleConfig)
	{
		exeLocation = _exeLocation;
		staticObstacleOutput = _staticObstacleOutput;
		dynamicObstacleRun = _dynamicObstacleRun;
		dynamicObstacleConfig = _dynamicObstacleConfig;
	}
private:
	string exeLocation;
	string staticObstacleOutput;
	string dynamicObstacleRun;
	string dynamicObstacleConfig;
};

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
	string _fileLocation;
	int random; //Replace with function for setting the seed?
	string _seed;
	string _SUMOexeLocation;
	Integer _port;
	vector<string> _AVid;
	TraCIAPI traci;
	dataMap currentData;
	dataMap _runData;
	dataMap _configData;
	Vector3 _bounds;

	LPWSTR cmdArgs;
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFO StartupInfo; //This is an [in] parameter
};



int main(int argc, char **argv1)
{
	
	

	// ask user for config file
	//get file location and name
	/*string fileName = "VASTConfig.xml";
	VAST *v = new VAST(fileName, fileName);
	cout << "Parsing begins...";
	v->Parse();
	cout << " parsing finished." << endl << endl;*/

	VAST *vast = new VAST();

	string fileName = "";
	cout << "Please type the configuration file location and name: ";
	cin >> fileName;

	vast->Parse(fileName);
	dataMap envMap = vast->_EnvConfig;
	vast->env = new UnityEnvironment();

	for (int i = 0; i < vast->_AVConfigs.size(); i++)
	{
		dataMap AVMap = vast->_AVConfigs[i];
		vector3 avLoc;
		avLoc.x = Vector3(AVMap[AV_LOCATION]).x();
		avLoc.y = Vector3(AVMap[AV_LOCATION]).y();
		avLoc.z = Vector3(AVMap[AV_LOCATION]).z();

		vector3 avBound;
		avBound.x = Vector3(AVMap[AV_BOUNDS]).x();
		avBound.y = Vector3(AVMap[AV_BOUNDS]).y();
		avBound.z = Vector3(AVMap[AV_BOUNDS]).z();

		vector3 avOrientation;
		avOrientation.x = Vector3(AVMap[AV_ORIENTATION]).x();
		avOrientation.y = Vector3(AVMap[AV_ORIENTATION]).y();
		avOrientation.z = Vector3(AVMap[AV_ORIENTATION]).z();

		vast->AVs.push_back(new GroundAV(AVMap[AV_NAME]->s_value(), avLoc, avBound, avOrientation, Integer(AVMap[AV_MOVEMENT_PORT]).value(), AVMap[AV_EXE_LOCATION]->s_value(), vast->_AVRun_Data));
	}
	

	//GroundAV *test = new GroundAV();


	
	//make example AVs and Environment (preferably from config file)

	
	cin.ignore();

	return 0;
}