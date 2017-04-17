#include "stdafx.h"
#include "Enemy.h"
#include <math.h>
#include "Player.h"
#include "Ladder.h"
#include "Floor.h"

Enemy::Enemy(std::string name) : GameObject(name)
{
	floorLock = nullptr; ladLock = nullptr; conflict = false; goal = nullptr;
	this->setPosition(sf::Vector2f(rand() % 1500, rand() % 1500));
	this->deathCountDown = 80;
	this->animation->minFrame = 0;
	this->animation->maxFrame = 1;
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

	//Commented out the "bob"
	//if (timer % 90 == 0)
	//	this->setvY(this->getVelocity().y * -1);

	if (stunned)
		stunnedTimer++;

	if (stunnedTimer == 120)
	{
		stunned = false;
		stunnedTimer = 0;
	}
	if (toDie == true){
		this->animation->setMinFrame(6);
		this->animation->setMaxFrame(9);
		this->setvX(0);
		this->setvY(0);
	}

	if (stunned)
	{
		setvX(0);
		setvY(0);
		animation->minFrame = 3;
		animation->maxFrame = 3;
		animation->setFrame(3);
	}
	else
	{
		animation->minFrame = 0;
		animation->maxFrame = 1;
	}

}

//method to determine what the best move is to find the player
void Enemy::findPlayer(Player* p)
{
	goal;
	sf::Vector2f positionDifference = position - p->getPosition();

	//Uncomment following for display of selected goal
	//if (goal != nullptr)
	//	goal->getAnimationSprite()->setColor(sf::Color::Blue);
	goal = pathFind(p, positionDifference);
	//if (goal != nullptr)
	//	goal->getAnimationSprite()->setColor(sf::Color::Green);

	if (gridLock(true, true) == nullptr)
	{
		conflict = true;
	}
	
	if (goal != nullptr)
		positionDifference = position - goal->getPosition();
	
	//TODO: Make it so the enemy gets closer to the player based on the positionDiffrence
	if (std::abs(positionDifference.x) > std::abs(positionDifference.y) && this->getfLock() == gridLock(false, false))
	{
		this->setvY(0);
		if (positionDifference.x > 0)
			this->setvX(-2);
		else
			this->setvX(2);
	}
	else if (this->getlLock() == gridLock(true, false))
	{
		this->setvX(0);
		if (positionDifference.y > 0)
			this->setvY(-2);
		else
			this->setvY(2);
	}

	this->setfLock(nullptr); this->setlLock(nullptr);
}


GameObject* Enemy::pathFind(Player* p, sf::Vector2f dif)
{
	Ladder* tmpL;
	Floor* tmpF;
	GameObject* goal = nullptr;
	std::vector<GameObject*> goals;

	if (this->getlLock() != nullptr)
	{
		//If top of Ladder set is closer to player than current difference
		tmpL = dynamic_cast<Ladder*>(getlLock())->getTop();
		if (abs(tmpL->getPosition().y - p->getPosition().y) < abs(dif.y))
			goals.push_back(tmpL);
		//If bot of Ladder set is closer to player than current difference
		tmpL = dynamic_cast<Ladder*>(getlLock())->getBot();
		if (abs(tmpL->getPosition().y - p->getPosition().y) < abs(dif.y))
			goals.push_back(tmpL);
	}
	if (this->getfLock() != nullptr)
	{
		//If right of floor set is closer to player than current difference
		tmpF = dynamic_cast<Floor*>(getfLock())->getRight();
		if (abs(tmpF->getPosition().x - p->getPosition().x) < abs(dif.x))
			goals.push_back(tmpF);
		//If left of floor set is closer to player than current difference
		tmpF = dynamic_cast<Floor*>(getfLock())->getLeft();
		if (abs(tmpF->getPosition().x - p->getPosition().x) < abs(dif.x))
			goals.push_back(tmpF);
	}

	if (!goals.empty())
	{
		goal = goals[0];
		for (int i = 1; i < goals.size(); i++)
		{
			if (sqrt(pow(goal->getPosition().x - p->getPosition().x, 2) + pow(goal->getPosition().y - p->getPosition().y, 2)) > sqrt(pow(goals[i]->getPosition().x - p->getPosition().x, 2) + pow(goals[i]->getPosition().y - p->getPosition().y, 2)))
				goal = goals[i];
		}
	}

	return goal;
}


GameObject* Enemy::gridLock(bool vertical, bool check = false)
{
	if (this->getlLock() != nullptr && this->getfLock() != nullptr) //If colliding with both ladder and floor
	{
		if (check == true) //When handleEvents is checking for the above situation
		{
			return nullptr; //Let handleEvents know by returning nullptr
		}
		else
		{
			if (vertical == true) 
				this->setfLock(nullptr);

			if (vertical == false) 
				this->setlLock(nullptr);
		}
	}

	//Ladder
	if (this->getlLock() != nullptr && this->getfLock() == nullptr)
	{
		this->setPosition(sf::Vector2f(this->getlLock()->getPosition().x, this->getPosition().y)); //Set x to ladder's x
		return this->getlLock();
	}
	//Floor
	else if (this->getfLock() != nullptr && this->getlLock() == nullptr)
	{
		//Set player y to on top of floor
		this->setPosition(sf::Vector2f(this->getPosition().x, this->getfLock()->getPosition().y - ((this->getfLock()->getAnimationSprite()->getGlobalBounds().height / 2) + (this->getAnimationSprite()->getGlobalBounds().height / 2)) + 2));
		return this->getfLock();
	}
}