#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(std::string name) : GameObject(name)
{
	this->animation->action = "walking";
	this->animation->minFrame = 0;
	this->animation->maxFrame = 1;
	this->setvY(-2);
	this->animation->setAnimationSpeed(10);
	this->animation->setScale(sf::Vector2f(3.5,3.5));

}


Enemy::~Enemy()
{
}

void Enemy::step()
{
	GameObject::step();

	if (this->vX > 0 && this->getDirection() == 0)
		this->flip();
	if (this->vX < 0 && this->getDirection() == 1)
		this->flip();

	if (timer % 90 == 0)
		this->setvY(this->getVelocity().y * -1);
	if (timer >= 600)
	{
		this->setvY(0);
		this->animation->minFrame = 2;
		this->animation->maxFrame = 2;
	}
}