#include "stdafx.h"
#include "Floor.h"

//floors are about 56 "units" wide
Floor::Floor() : Structure("floor")
{
	animation->setScale(sf::Vector2f(0.75, 0.75));
}


Floor::Floor(Floor* left, Floor* right) : Structure("floor")
{
	animation->setScale(sf::Vector2f(0.75, 0.75));
	rSide = right; lSide = left;
}


Floor::~Floor()
{
}
