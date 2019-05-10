#include "gtest/gtest.h"
#include "ScenarioMetric.h"
#include "LargestDeltaPosition.h"

/* Default test - should always succeed.*/
TEST(Test_ScenarioMetrics, DefaultTrueMetricTest)
{
	EXPECT_TRUE(true);
}

/* MetricConstructors - Tests that each Scenario Metric can be created without error.
Procedure: Create one of each extended ScenarioMetric and verify no exceptions.
Pass: No exceptions in creating or destroying the ScenarioMetrics.
Fail: An exception was thrown.
*/

//example AV
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
class TestEnv : public Environment
{
public:
	TestEnv() {};
	TestEnv(string _exeLocation, string _staticObstacleOutput, string _dynamicObstacleRun, string _dynamicObstacleConfig)
	{
		exeLocation = _exeLocation;
		staticObstacleOutput = _staticObstacleOutput;
		dynamicObstacleRun = _dynamicObstacleRun;
		dynamicObstacleConfig = _dynamicObstacleConfig;
	}

	void Initialize() {};
	void Update() {};
	void Connect() {};
	void Close() {};
	void addAV(AV *AV) { };

private:
	string exeLocation;
	string staticObstacleOutput;
	string dynamicObstacleRun;
	string dynamicObstacleConfig;
};

TEST(Test_ScenarioMetrics, MetricDestructor)
{
	ScenarioMetric *test = new LargestDeltaPosition();

	// TEST: that each ScenarioMetric type can be created with no thrown exceptions
	EXPECT_NO_THROW(test = new LargestDeltaPosition(new TestAV(), new TestEnv()););

	// TEST: that each ScenarioMetric can be deleted with no thrown exceptions
	EXPECT_NO_THROW(delete test);
}