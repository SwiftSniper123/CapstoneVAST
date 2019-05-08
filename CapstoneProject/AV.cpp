#include "AV.h"



AV::AV()
{
}


AV::~AV()
{
}

void AV::runScript()
{
	//executes the python script from the console to allow the AV to control itself
	string command = "python ";
	command += exe;
	system(command.c_str());
}