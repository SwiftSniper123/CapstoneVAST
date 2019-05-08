#include <iostream>
#include <Windows.h>
#include <string>
#include "VAST.h"

using namespace std;

//AV example
class GroundAV : AV
{
public:
	GroundAV(vector3 _position, vector3 _bounds, vector3 _rotation) : AV(_position, _bounds, _rotation) {};
};
//Environment example
class UnityEnvironment : Environment
{
public:
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

	/*string fileName = "";
	cout << "Please type the configuration file location and name: ";
	cin >> fileName;*/
	
	//make example AVs and Environment (preferably from config file)

	//


	return 0;
}