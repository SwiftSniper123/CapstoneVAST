#include "SumoEnvironment.h"

SumoEnvironment::SumoEnvironment(string _configFileLocation, string _SUMOexeLocation, int _port, vector3 _bounds)
{
	fileLocation = _configFileLocation;
	SUMOexeLocation = _SUMOexeLocation;
	port = _port;
	bounds = _bounds;
}

LPWSTR ConvertString(const std::string& instr)
{
	// Assumes std::string is encoded in the current Windows ANSI codepage
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

	if (bufferlen == 0)
	{
		// Something went wrong. Perhaps, check GetLastError() and log.
		throw InvalidArgumentException("Error converting command arguments.");
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


void SumoEnvironment::update(timestamp t, dataMap dataMap)
{
	EventTree *eventTree = this->getEventTree();

	if (eventTree->getCurrentSimTime() == -1)
	{
		currentData = callUpdateFunctions();
		cout << "\nUpdating Environment Data\n";
		this->getEventTree()->addEvent(this, t, currentData);
		return;
	}
	//currentData[DURATION] = new Double(1.0);
	//currentData[TARGET_VELOCITY] = new Double(1.0);

	currentData = callUpdateFunctions();
	cout << "\nUpdating Environment Data\n";
	this->getEventTree()->addEvent(this, t, currentData);
	traci.simulationStep();
}

void SumoEnvironment::openEnvironment()
{
	string str = _SUMOexeLocation;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo)); //Fills StartupInfo with zeros
	StartupInfo.cb = sizeof StartupInfo; //Only parameter of StartupInfo that needs to be configured

	if (_seed == "r" || _seed == "R")
	{
		srand(time(NULL)); //Provides a seed for the random number generator

		int seed = rand() % 10000; //Generates a random seed for Sumo

		str = _SUMOexeLocation + " -c " + _fileLocation + " --remote-port 1337" + " --seed " + std::to_string(seed);

	}

	else if (!_seed.empty())
	{
		str = _SUMOexeLocation + " -c " + _fileLocation + " --remote-port 1337" + " --seed " + _seed;
	}

	else
		str = _SUMOexeLocation + " -c " + _fileLocation + " --remote-port 1337";

	cmdArgs = ConvertString(str);

	CreateProcess(NULL, cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo);

	Sleep(5000);

	traci.connect("localhost", 1337);
	traci.simulationStep();

	//traci.close(); // why are we closing here??
	std::cout << "\nOpening connection to SUMO.\n" << "TEST Traci: " << traci.simulation.getTime();
	this->getEventTree()->start();

	return;
}

void SumoEnvironment::getMapInformation()
{
	//int IDcount = traci.vehicle.getIDCount();

	vector<string> IDlist = traci.vehicle.getIDList();
	vector<VType*> vehicleIDs;
	vector<VType*> positions;
	vector<VType*> velocities;
	vector<VType*> accelerations;


	// iterate through the list of SUMO vehicle ids
	for (int i = 0; i < IDlist.size(); i++)
	{
		string veh = IDlist[i];
		vehicleIDs.push_back(new String(veh)); // place the vehicle id in the array
		// query SUMO via traci methods and compile datamap data
		libsumo::TraCIPosition XYZ(traci.vehicle.getPosition(veh));
		positions.push_back(new Vector3(XYZ.x, XYZ.y, XYZ.z));
		velocities.push_back(new Double(traci.vehicle.getSpeed(veh)));
		accelerations.push_back(new Double(traci.vehicle.getAcceleration(veh)));
	}

	// put data in the map under these runData keys
	currentData[OBSTACLE_IDS] = new Array(vehicleIDs);
	currentData[OBSTACLE_POS] = new Array(positions);
	currentData[OBSTACLE_VEL] = new Array(velocities);
	currentData[OBSTACLE_ACC] = new Array(accelerations);
}

void SumoEnvironment::changeAVCommand()
{
	String one("1");
	String zero("0");

	double speed, duration;

	speed = stod(currentData["TargetVelocity"]->s_value());
	duration = stod(currentData["Duration"]->s_value());

	for (vector<string>::iterator av = _AVid.begin(); av != _AVid.end(); av++)
	{
		if (currentData["AVLogic"] == &one)
		{
			traci.vehicle.slowDown(*av, speed, duration);
		}
		if (currentData["AVLogic"] == &zero)
		{
			traci.vehicle.setSpeed(*av, speed * 2);
		}
	}
}

void SumoEnvironment::setSeed(string seed)
{
	_seed = seed;
}

void SumoEnvironment::addAV(AV *AV)
{
	_AVid.push_back(AV->getName());
}

dataMap SumoEnvironment::callUpdateFunctions()
{
	//changeAVCommand();
	getMapInformation();
	return currentData;
}

void SumoEnvironment::stopReplication(bool another, string runID)
{

}