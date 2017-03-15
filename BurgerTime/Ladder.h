#pragma once
#include "Structure.h"

//ladder is about 75 "units" tall
class Ladder : public Structure
{
public:
	Ladder();
	~Ladder();
private:
	int height;
};

