#include "stdafx.h"
#include "Item.h"


Item::Item(std::string fileName): GameObject(fileName)
{
	animation->setScale(sf::Vector2f(2.5, 2.5));
	
}


Item::~Item()
{
}
