#include "stdafx.h"
#include "Enemy.h"
#include <math.h>
#include "Player.h"

Enemy::Enemy(std::string name) : GameObject(name)
{
	this->setPosition(sf::Vector2f(rand() % 1500, rand() % 1500));
	this->deathCountDown = 20;
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

	if (timer % 200 == 0)
	{
		setvY(0);
		die();
	}
}

//method to determine what the best move is to find the player
void Enemy::findPlayer(Player* p)
{
	sf::Vector2f positionDifference = position - p->getPosition();
	std::cout << positionDifference.x << std::endl;

	//TODO: Make it so the enemy gets closer to the player based on the positionDiffrence
}
