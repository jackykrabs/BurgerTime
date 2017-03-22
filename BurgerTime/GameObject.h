
#include <SFML/Graphics.hpp>
#include "Animation.h"

#pragma once
class GameObject
{
public:
	GameObject();
	GameObject(std::string);
	~GameObject();

	virtual void step();
	void Collision(GameObject);
	void updateClipart();
	sf::Sprite mySprite;

	virtual void die();

	int getDeathCountDown() { return deathCountDown;  }

	void setToDie(bool toDie) { this->toDie = toDie; }
	bool getToDie() { return toDie; }

	int getTimer() { return timer; }
	int getDeathTimer() { return deathTimer; }

	void move(sf::Vector2f);
	sf::Vector2f getVelocity() { return velocity; }

	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition() { return position; }

	void setvX(double x) { velocity.x = x; }
	void setvY(double y) { velocity.y = y; }

	void setX(double x);
	void setY(double y);

	int getDirection() { return animation->getDirection(); }
	void setDirection(int direction) { animation->setDirection(direction); }

	void flip() { animation->flip(); }

	std::string getAction() { return animation->getAction(); }
	void setAction(std::string action){ animation->setAction(action); }

	void processName() { animation->processName(); }
	sf::Sprite* getAnimationSprite() { return animation->getSprite(); }
protected:
	bool toDie;
	Animation* animation;
	sf::Texture myTexture;
	double vX;
	double vY;
	int deathCountDown;
	int timer;
	int deathTimer;
	sf::Vector2f velocity;
	sf::Vector2f position;
	double x;
	double y;
	int team;
};

