#include "gtest/gtest.h"
#include "VAST.h"

/*Default true test*/
TEST(Test_VAST, TrueInTestVASTLibrary)
{
	ASSERT_TRUE(true);
}

/*Tests base VAST class constructor.*/
TEST(Test_VAST, Constructor)
{
	VAST *v = new VAST();
	ASSERT_NO_FATAL_FAILURE(VAST *v = new VAST());

	ASSERT_NO_FATAL_FAILURE(delete v);
}

//Sample AV
class TestAV : public AV
{
public:
	TestAV() {};
	TestAV(string _name, vector3 _position, vector3 _bounds, vector3 _rotation, int _port, string _exe, dataMap _AVMap)
		: AV(_name, _position, _bounds, _rotation, _port, _exe)
	{
		AVMap = _AVMap;
	};
	void Initialize()
	{

	}
	void Update()
	{
		//this->position.x += 1;
		//this->position.z = -2;
	}
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


//Verifies Parsing is constructing the AVs and Environments properly
TEST(Test_VAST, Parse)
{
	VAST *v = new VAST();
	ASSERT_NO_THROW(v->Parse("VASTConfig.xml"));



	delete v;
	// Populate datamap based on results from parsing
	// Commpare value to verify the configuration map was filled properly
	//dataMap env = p->_Env->getDataMap();
	//ASSERT_TRUE(env.size() > 0);
	//ASSERT_TRUE(Integer(env.at("env_obstacle_port")).value() == 12345);

	//ASSERT_NO_FATAL_FAILURE(p->_AV.at(0))

	//VType test = p->_EnvRun_Data.find("env_obstacle_port");
	//std::cout << p->env->_env_obstacle_port.value();
	//ASSERT_TRUE(p->env->_env_obstacle_port == Integer);
}