#include "stdafx.h"
#include "PepperShot.h"

//create a new pepper shot at the location of 'o'
PepperShot::PepperShot(GameObject* o) : GameObject("pepper_shot")
{
	this->animation->setMinFrame(0);
	this->animation->setMaxFrame(3);
	this->animation->setAnimationSpeed(6);

	if (o->getDirection() == 1)
		this->setPosition(sf::Vector2f(o->getPosition().x + 50, o->getPosition().y));
	else
		this->setPosition(sf::Vector2f(o->getPosition().x - 100, o->getPosition().y));
}


PepperShot::~PepperShot()
{
}

void PepperShot::step()
{
	GameObject::step();

}