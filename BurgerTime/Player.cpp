#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"

//TODO: print the information on the players position in order to decide where to make the spawn miester
Player::Player() : GameObject("pepper")
{
	floorLock = nullptr; ladLock = nullptr;
	animation->setScale(sf::Vector2f(5,5));
	deathCountDown = 1;
	this->setOriginalPosition(sf::Vector2f(850,600));
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
		animation->setAnimationSpeed(14);
	}
	else if (action == "stillSide")
	{
		animation->setMinFrame(5);
		animation->setMaxFrame(5);
		animation->setAnimationSpeed(14);
	}
	else if (action == "still")
	{
		animation->setMinFrame(0);
		animation->setMaxFrame(0);
		animation->setAnimationSpeed(14);
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
	else if (action == "dying")
	{
		animation->setMinFrame(14);
		animation->setMaxFrame(19);
		animation->setAnimationSpeed(23);
	}

	this->animation->setFrame(this->animation->getMinFrame());
	this->animation->updateOrigin();
}
