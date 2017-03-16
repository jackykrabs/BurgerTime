#include "stdafx.h"
#include "PepperShot.h"

//create a new pepper shot at the location of 'o'
PepperShot::PepperShot(GameObject* o) : GameObject("pepper_shot")
{
	this->animation->setMinFrame(0);
	this->animation->setMaxFrame(3);
	this->animation->setAnimationSpeed(6);
	this->setPosition(o->getPosition());
}


PepperShot::~PepperShot()
{
}

void PepperShot::step()
{
	GameObject::step();
	if (timer % 20 == 0)
		this->~PepperShot();
}