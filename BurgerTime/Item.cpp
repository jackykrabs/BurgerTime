#include "stdafx.h"
#include "Item.h"


Item::Item() : GameObject("hotdog")
{
	animation->setScale(sf::Vector2f(5, 5));
	animation->setPosition(100, 100);

}


Item::~Item()
{
}
