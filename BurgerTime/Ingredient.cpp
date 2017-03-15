#include "stdafx.h"
#include "Ingredient.h"


Ingredient::Ingredient(std::string ingredientName) : GameObject(ingredientName)
{
	hasWalked = false;
}


Ingredient::~Ingredient()
{
}
