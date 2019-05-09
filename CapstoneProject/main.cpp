#include <iostream>
#include <Windows.h>
#include <string>
#include "VAST.h"
#include "SumoEnvironment.h"

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
	vast->env = new SumoEnvironment();

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
	



	//run VAST
	vast->Run();

	cin.ignore();


	//launch post-sim executable if the post-sim box is checked
	//if (vast->_VASTConfigMap[VIZ])
	if (vast->_VASTConfigMap[VIZ])
		system("TestAutonomousVehicleDemo.exe");

	return 0;
}