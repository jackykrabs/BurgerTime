#include "stdafx.h"
#include "PepperShot.h"

//create a new pepper shot at the location of 'o'
PepperShot::PepperShot(GameObject* o) : GameObject("pepper_shot")
{
	this->deathCountDown = 20;
	this->toDie = true;
	this->animation->setMinFrame(0);
	this->animation->setMaxFrame(3);
	this->animation->setAnimationSpeed(6);
	initializePosition(false, o);
}

//create a new peppershot at the location of 'o', but the bool indicates
//if it's above or below
PepperShot::PepperShot(GameObject* o, bool isAbove) : PepperShot(o)
{
	if (isAbove)
		this->move(sf::Vector2f(50, -100));
	else
		this->move(sf::Vector2f(0, 30));
	initializePosition(true, o);
}
PepperShot::~PepperShot()
{
}

void PepperShot::step()
{
	GameObject::step();
}

void PepperShot::initializePosition(bool isClimbing, GameObject* o)
{
	if (!isClimbing)
	{

		if (o->getDirection() == 1)
			this->setPosition(sf::Vector2f(o->getPosition().x + 50, o->getPosition().y));
		else
			this->setPosition(sf::Vector2f(o->getPosition().x - 100, o->getPosition().y));
	}
	else
	{
		this->setPosition(sf::Vector2f(o->getPosition().x, o->getPosition().y - 100));
	}
}