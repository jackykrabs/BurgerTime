#pragma once
#include "GameObject.h"

class Ingredient : GameObject
{
public:
	Ingredient();
	~Ingredient();
private:
	bool hasWalked;
};

