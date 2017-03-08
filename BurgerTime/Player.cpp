#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"

Player::Player() : GameObject("pepper")
{
	animation->setScale(sf::Vector2f(5,5));
}


Player::~Player()
{
}
