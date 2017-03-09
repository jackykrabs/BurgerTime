#include "stdafx.h"
#include "Item.h"


Item::Item() : GameObject("coffee")
{
	animation->setScale(sf::Vector2f(2.5, 2.5));
	
}


Item::~Item()
{
}
