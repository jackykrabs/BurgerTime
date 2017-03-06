#pragma once
#include "Ingredient.h"
#include <vector>

class Burger
{
public:
	Burger();
	~Burger();
private:
	bool isComplete;
	std::vector<Ingredient> ingredient;
};

