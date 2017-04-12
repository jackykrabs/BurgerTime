#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"


Player::Player() : GameObject("pepper")
{
	floorLock = nullptr; ladLock = nullptr;
	animation->setScale(sf::Vector2f(5,5));
	deathCountDown = 1;
}


Player::~Player()
{
}

//method specifically for 'Player' to set the animation stuff
void Player::processAction()
{
	if (action == "walking")
	{
		animation->setMinFrame(5);
		animation->setMaxFrame(6);
	}
	else if (action == "stillSide")
	{
		animation->setMinFrame(5);
		animation->setMaxFrame(5);
	}
	else if (action == "still")
	{
		animation->setMinFrame(0);
		animation->setMaxFrame(0);
	}
	else if (action == "throwing")
	{
		animation->setMinFrame(11);
		animation->setMaxFrame(11);
	}
	else if (action == "climbing")
	{
		animation->setMinFrame(12);
		animation->setMaxFrame(13);
	}

	this->animation->setFrame(this->animation->getMinFrame());
	this->animation->updateOrigin();
}
