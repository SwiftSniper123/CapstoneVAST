#include "SumoEnvironment.h"

SumoEnvironment::SumoEnvironment(string _configFileLocation, string _SUMOexeLocation, int _port, vector3 _bounds, dataMap _envMap) : Environment(_configFileLocation, _SUMOexeLocation, _port, _bounds)
{
	envMap = _envMap;
}

LPWSTR ConvertString(const std::string& instr)
{
	// Assumes std::string is encoded in the current Windows ANSI codepage
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

	if (bufferlen == 0)
	{
		// Something went wrong. Perhaps, check GetLastError() and log.
		//throw InvalidArgumentException("Error converting command arguments.");
	}

	// Allocate new LPWSTR - must deallocate it later
	LPWSTR widestr = new WCHAR[bufferlen + 1];

	::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

	// Ensure wide string is null terminated
	widestr[bufferlen] = 0;

	// Do something with widestr
	return widestr;
	//delete[] widestr;
}


void SumoEnvironment::Update()
{
	//currentData[DURATION] = new Double(1.0);
	//currentData[TARGET_VELOCITY] = new Double(1.0);

	//cout << "\nUpdating Environment Data\n";
	for (int i = 0; i < AVs.size(); i++)
	{
		traci.vehicle.moveToXY(AVs[i]->name, "1to2", 0, AVs[i]->position.x, AVs[i]->position.y, AVs[i]->rotation.y, 2);
		//std::cout << "\nAV pos: " << traci.vehicle.getPosition(AVs[i]->name).getString();
	}

	/*std::cout << "\nAV vel: " << traci.vehicle.getSpeedWithoutTraCI(AVs[0]->name);
	std::cout << "\nAV accel: " << traci.vehicle.getAccel(AVs[0]->name);*/

	std::vector<string> objList = traci.vehicle.getIDList();

	for (int n = 0; n < objList.size(); n++)
	{
		bool instObj = true;
		for (int a = 0; a < AVs.size(); a++)
		{
			if (objList[n] == AVs[a]->name)
				instObj = false;
		}

		for (int i = 0; i < dynamicObstacles.size(); i++)
		{
			if (objList[n] == dynamicObstacles[i]->_name)
			{
				dynamicObstacles[i]->_position.x = traci.vehicle.getPosition(objList[n]).x;
				dynamicObstacles[i]->_position.y = 0;
				dynamicObstacles[i]->_position.z = traci.vehicle.getPosition(objList[n]).y;

				dynamicObstacles[i]->_rotation.x = 0;
				dynamicObstacles[i]->_rotation.y = traci.vehicle.getAngle(objList[n]);
				dynamicObstacles[i]->_rotation.z = 0;

				instObj = false;
			}
		}

		if (instObj)
		{
			vector3 tempPos;
			tempPos.x = traci.vehicle.getPosition(objList[n]).x;
			tempPos.y = 0;
			tempPos.z = traci.vehicle.getPosition(objList[n]).y;

			vector3 tempBounds;
			tempBounds.x = 3;
			tempBounds.y = 2;
			tempBounds.z = 2;

			vector3 tempRotation;
			tempRotation.x = 0;
			tempRotation.y = traci.vehicle.getAngle(objList[n]);
			tempRotation.z = 0;

			//std::cout << "\nObst '" << objList[n] << "' pos: " << traci.vehicle.getPosition(objList[n]).getString();

			dynamicObstacles.push_back(new Obstacle(objList[n], tempPos, tempBounds, tempRotation));
		}

		//objList.clear();
	}
	traci.simulationStep();
}

void SumoEnvironment::Initialize()
{
	string str;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo)); //Fills StartupInfo with zeros
	StartupInfo.cb = sizeof StartupInfo; //Only parameter of StartupInfo that needs to be configured

	if (seed == "r" || seed == "R")
	{
		srand(time(NULL)); //Provides a seed for the random number generator

		int seed = rand() % 10000; //Generates a random seed for Sumo
		
		str = exeLocation + " -c " + configFileLocation + " --no-step-log --remote-port 1337 --seed " + std::to_string(seed);
	}

	else if (!seed.empty())
	{
		str = exeLocation + " -c " + configFileLocation + " --no-step-log --remote-port 1337 --seed " + seed;
	}

	else
		str = exeLocation + " -c " + exeLocation + " --no-step-log --remote-port 1337";

	//cmdArgs = ConvertString(str);
	cmdArgs = const_cast<char *>(str.c_str());

	CreateProcess(NULL, cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo);

	std::cout << "\nOpening SUMO\n";
	Sleep(5000);
}

void SumoEnvironment::Connect()
{
	traci.connect("localhost", 1337);
	//traci.setOrder(1);
	//traci.close(); // why are we closing here??
	std::cout << "\nConnecting to SUMO.\n";
	//this->getEventTree()->start();
}

void SumoEnvironment::Close()
{
	traci.close();
}

void SumoEnvironment::setSeed(string _seed)
{
	seed = _seed;
}

void SumoEnvironment::addAV(AV *AV)
{
	AVs.push_back(AV);
	//string pos = std::to_string(AV->position.x) + "," + std::to_string(AV->position.y) + "," + std::to_string(AV->position.z);
	traci.vehicle.add(AV->name, "route0", "Car", "0");
	traci.vehicle.moveToXY(AV->name, "1to2", 0, AV->position.x, AV->position.z, AV->rotation.y, 2);
	//std::cout << "\nvehicle position: " << traci.vehicle.getPosition(AV->name).getString();
}

void SumoEnvironment::stopReplication(bool another, string runID)
{

}