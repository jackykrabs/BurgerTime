
#include <SFML/Graphics.hpp>
#include "Animation.h"

#pragma once
class GameObject
{
public:
	GameObject();
	GameObject(std::string);
	~GameObject();

	void step();
	void Collision(GameObject);
	void updateClipart();
	sf::Sprite mySprite;

	sf::Vector2f getVelocity() { return velocity; }

	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition() { return position; }

	void setvX(double x) { velocity.x = x; }
	void setvY(double y) { velocity.y = y; }

	void setX(double x);
	void setY(double y);

	sf::Sprite getAnimationSprite(){ return animation->getSprite(); }
protected:
	Animation* animation;
	sf::Texture myTexture;
	double vX;
	double vY;

	int timer;
	sf::Vector2f velocity;
	sf::Vector2f position;
	double x;
	double y;
	int team;
};

