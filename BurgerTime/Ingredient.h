#pragma once
#include "GameObject.h"

class Ingredient : public GameObject
{
public:
	Ingredient(std::string);
	~Ingredient();
private:
	bool hasWalked;
};

