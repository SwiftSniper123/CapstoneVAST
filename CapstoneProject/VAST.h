#pragma once
#include "AV.h"
#include "Environment.h"
#include <vector>

class VAST
{
public:
	VAST();
	VAST(std::vector<AV*> _AVs, Environment* _env);
	~VAST();
	std::vector<AV*> AVs;
	Environment* env;
};

