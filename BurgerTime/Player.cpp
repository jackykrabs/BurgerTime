#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"

Player::Player() : GameObject("pepper")
{
	animation = new Animation("pepper", "still", 4);
	animation->setScale(sf::Vector2f(5,5));
}


Player::~Player()
{
}
