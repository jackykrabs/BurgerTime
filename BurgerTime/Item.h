#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item(std::string);
	~Item();


private:
	int pointValue;
};

