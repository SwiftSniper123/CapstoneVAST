#include "VAST.h"

VAST::VAST()
{
}

VAST::~VAST()
{
}

void VAST::Parse(string _file)
{
	ptree pt1;

	// Variables to track current position in the xml structure
	string _currentKey; 
	string _currentModule; // Current overarching module
	string _currentValue; 
	string _type;
	const string _delim = ", "; // Used when parsing optional fields

	try {
		read_xml(_file, pt1);
	}
	catch (const std::exception& e) {
		cout << "Invalid File. Ending.";
		return;
	}
	try
	{
		BOOST_FOREACH(ptree::value_type const& node, pt1.get_child(VAST_MODULE))
		{
			boost::property_tree::ptree subtree = node.second;

			if (node.first == MODULE)
			{
				_currentModule = subtree.get<string>("<xmlattr>.module");

				BOOST_FOREACH(boost::property_tree::ptree::value_type const& map, subtree.get_child(MAP))
				{
					boost::property_tree::ptree subMap = map.second;

					BOOST_FOREACH(boost::property_tree::ptree::value_type const& pair, subMap.get_child(""))
					{
						boost::property_tree::ptree key = pair.second;

						string label = pair.first;
						if (label != "<xmlattr>")
						{
							if (label == KEY)
							{
								_currentKey = key.get<string>(NAME);
							}

							else if (label == VALUE)
							{
								_currentValue = key.get<string>(NAME);

								if (_currentValue != "")
								{
									if (_currentModule == VAST_MODULE)
									{
										if (_currentKey == OUTPUT_FILE)
										{
											String *v = new String(key.get<string>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == VIZ)
										{
											Boolean *v = new Boolean(key.get<bool>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == TIME_RATIO)
										{
											Double *v = new Double(key.get<double>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == TIME_STEP)
										{
											Double *v = new Double(key.get<double>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == NUM_REPLCATION)
										{
											Integer *v = new Integer(key.get<int>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == SEEDS)
										{
											Array *v = new Array(key.get<string>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == MAX_RUN_TIME)
										{
											Double *v = new Double(key.get<double>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
										else if (_currentKey == METRICS)
										{
											Array *v = new Array(key.get<string>(NAME));
											_VASTConfigMap.insert(namedData(_currentKey, v));
										}
									}

									if (_currentModule == ENVIRONMENT_MODULE)
									{
										if (_currentKey == ENV_OBSTACLE_PORT)
										{
											Integer *v = new Integer(key.get<int>(NAME));
											_EnvConfig[_currentKey] = v;
										}
										else if (_currentKey == EXE_LOCATION)
										{
											String *v = new String(key.get<string>(NAME));
											_EnvConfig[_currentKey] = v;
										}
										else if (_currentKey == ENV_BOUNDS)
										{
											Vector3 *v = new Vector3(key.get<string>(NAME));
											_EnvConfig[_currentKey] = v;
										}
										else if (_currentKey == CONFIG_LOCATION)
										{
											String *v = new String(key.get<string>(NAME));
											_EnvConfig[_currentKey] = v;
										}
										else
										{
											// gathering run data fields
											size_t pos = _currentValue.find(_delim);
											size_t endPos = _currentValue.find(_delim) + 2;
											string _valCopy = _currentValue;
											_type = _valCopy.substr(0, pos);
											_currentValue = _currentValue.substr(endPos);

											fillMap(_currentModule, _EnvRun_Data, _type, _currentKey, _currentValue);
										}
									}

									else if (_currentModule == AV_MODULE)
									{
										if (_currentKey == AV_NAME)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												String *v = new String(val);
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == AV_MOVEMENT_PORT)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												Integer *v = new Integer(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == AV_EXE_LOCATION)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												String *v = new String(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == AV_LOCATION)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												Vector3 *v = new Vector3(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == AV_ORIENTATION)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												Vector3 *v = new Vector3(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == AV_BOUNDS)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												Vector3 *v = new Vector3(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else if (_currentKey == SENSORS)
										{
											string val = key.get<string>(NAME);
											if (!val.empty()) {
												Array *v = new Array(new VType(val));
												_AVConfig[_currentKey] = v;
											}
										}
										else
										{
											size_t pos = _currentValue.find(_delim);
											size_t endPos = _currentValue.find(_delim) + 2;
											string _valCopy = _currentValue;
											_type = _valCopy.substr(0, pos);
											_currentValue = _currentValue.substr(endPos);

											fillMap(_currentModule, _AVRun_Data, _type, _currentKey, _currentValue);
										}
									}
								}
							}
						}
					}
				}

				// Module specific tasks
				if (_currentModule == "AV")
				{
					//Add config maps to a vector to support multiple AVs.
					_AVConfigs.push_back(_AVConfig);
				}
				else if (_currentModule == "Environment")
				{
					
				}
				else if (_currentModule == "VAST")
				{
					
				}
			}
		}
	}
	catch(...)
	{
		cerr << "Error parsing file";
		return;
	}
}

// Parses fields that are "Optional" and inserts them into the run_Data map
void VAST::fillMap(string currentModule, dataMap &run_Data, string type, string key, string value)
{
	char first = type.at(0);
	VType *v;

	String *s;
	Double *d;
	Integer *i;
	Boolean *b;
	Vector3 *vec;
	Array *a;

	switch (first)
	{
	case 's':
	case 'S':
		s = new String(new VType(value));
		v = s;
		break;
	case 'd':
	case 'D':
		d = new Double(new VType(value));
		v = d;
		break;
	case 'i':
	case 'I':
		i = new Integer(new VType(value));
		v = i;
		break;
	case 'b':
	case 'B':
		b = new Boolean(new VType(value));
		v = b;
		break;
	case 'v':
	case 'V':
		vec = new Vector3(new VType(value));
		v = vec;
		break;
	case 'a':
	case 'A':
		a = new Array(new VType(value));
		v = a;
		break;
	}

	if (currentModule == ENVIRONMENT_MODULE)
	{
		run_Data.emplace(namedData(key, v));
	}
	else if (currentModule == AV_MODULE)
	{
		run_Data.emplace(namedData(key, v));
	}
}

void VAST::publishMetrics()
{
	Metrics.open(MetricsFileName, std::ios_base::out);
	Metrics << "Run_ID, AV_ID, Metric_Name, Metric_Value" << endl;

	for (int n = 0; n < metrics.size(); n++)
		for (int m = 0; m < metrics[n].size(); m++)
			Metrics << "0," + metrics[n][m]->av->name + "," +metrics[n][m]->name + "," + std::to_string(metrics[n][m]->value) << endl;

	Metrics.close();
}

void VAST::Run()
{
	ZeroMemory(&StartupInfo, sizeof(StartupInfo)); //Fills StartupInfo with zeros
	StartupInfo.cb = sizeof StartupInfo; //Only parameter of StartupInfo that needs to be configured

	//open the collision detection module
	string str = "CollisionDetection/CollisionDetection.exe";
	cmdArgs = const_cast<char *>(str.c_str());

	/*//executes the external module
	CreateProcess(NULL, cmdArgs,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo);*/

	

	timeStep = Double(_VASTConfigMap[TIME_STEP]).value();

	cout << "\nBeginning Run...\n-------------------------------------------------------------------" << endl;

	RunData.open(RunDataFileName, std::ios_base::out);
	RunData << "Run_ID,Time,Obj_ID,Obj_X,Obj_Y,Obj_Z,Obj_Angle" << endl;

	env->Initialize();
	for (int i = 0; i < AVs.size(); i++)
	{
		AVs[i]->Initialize();
	}

	env->Connect();
	
	//initialize AV collision table
	AVColDetInit.open(AVColDetInitFileName, std::ios_base::out);
	for (int i = 0; i < AVs.size(); i++)
	{
		env->addAV(AVs[i]);
		AVColDetInit << runID << "," << AVs[i]->name << "," << AVs[i]->bounds.x << "," << AVs[i]->bounds.y << "," << AVs[i]->bounds.z << endl; //write the AV initialization information
	}
	AVColDetInit.close();
	
	//execute the program until the max run time is achieved
	while (currentSimTime < Double(_VASTConfigMap[MAX_RUN_TIME]).value())
	{
		cout << "Run: " << runID <<", Sim Time: " << currentSimTime << "\n";

		//update environment		
		env->Update();
		
		//output run data each time step
		//get states of AVs and publish information to files
		AVColDetInfo.open(AVColDetInfoFileName);
		for (int nA = 0; nA < AVs.size(); nA++)
		{
			AVs[nA]->Update();

			RunData << "0," << currentSimTime << "," << AVs[nA]->name << "," << AVs[nA]->position.x << "," << AVs[nA]->position.y
				<< "," << AVs[nA]->position.z << "," << AVs[nA]->rotation.y << endl;

			//add existing data point
			AVColDetInfo << "0," << currentSimTime << "," << AVs[nA]->name << "," << AVs[nA]->position.x << "," << AVs[nA]->position.y 
				<< "," << AVs[nA]->position.z << "," << AVs[nA]->rotation.y << endl;
		}
		AVColDetInfo.close();

		//add obstacle information
		ObsColDetInfo.open(ObsColDetInfoFileName);
		for (int n = 0; n < env->dynamicObstacles.size(); n++)
		{
			RunData << "0," << currentSimTime << "," << env->dynamicObstacles[n]->_name << "," << env->dynamicObstacles[n]->_position.x << ","
				<< env->dynamicObstacles[n]->_position.y << "," << env->dynamicObstacles[n]->_position.z << "," << env->dynamicObstacles[n]->_rotation.y << endl;

			//add existing data point
			ObsColDetInfo << "0," << currentSimTime << "," << env->dynamicObstacles[n]->_name << "," << env->dynamicObstacles[n]->_position.x << ","
				<< env->dynamicObstacles[n]->_position.y << "," << env->dynamicObstacles[n]->_position.z << "," << env->dynamicObstacles[n]->_rotation.y << ","
				<< env->dynamicObstacles[n]->_bounds.x << "," << env->dynamicObstacles[n]->_bounds.y << "," << env->dynamicObstacles[n]->_bounds.z << endl;
		}
		ObsColDetInfo.close();

		//calculate metrics
		for (int a = 0; a < metrics.size(); a++)
			for (int m = 0; m < metrics[a].size(); m++)
				metrics[a][m]->calculate();

		//advance current time to the environment time
		currentSimTime += timeStep;
	}

	env->Close();
	//publish metrics
	publishMetrics();

	RunData.close();

	cout << "\nRun ends" << endl;
	
}