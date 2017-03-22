// GameObject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

using namespace std;
GameObject::GameObject()
{

}

GameObject::GameObject(std::string fileName)
{
	animation = new Animation(fileName, "still", 4);
	timer = 0;
	deathTimer = 0;

	//default value of death countdown
	deathCountDown = 80;

	sf::Image myImage;
	myImage.loadFromFile("images//"+fileName);
	myTexture.loadFromImage(myImage);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(mySprite.getTextureRect().width / 2, mySprite.getTextureRect().height);
	mySprite.scale(5, 5);
	animation->setScale(sf::Vector2f(5, 5));
}


GameObject::~GameObject()
{
}

void GameObject::updateClipart()
{
	sf::Image anotherImage;
	anotherImage.loadFromFile("sasser.jpg");
	myTexture.loadFromImage(anotherImage);
}

//called every frame to update good times
void GameObject::step()
{
	if (timer % animation->getAnimationSpeed() == 0)
	{
		if (animation->getMaxFrame() <= animation->getFrame())
			animation->setFrame(animation->getMinFrame());
		else
			animation->setFrame(animation->getFrame() + 1);
	}

	this->setPosition(getAnimationSprite()->getPosition());
	//iterate timer
	timer++;
	if (toDie)
		deathTimer++;
}

//method to begin the dying process
void GameObject::die()
{
	toDie = true;
	animation->minFrame = 7;
	animation->maxFrame = 10;
	animation->setFrame(7);
}

//set the overall position
//precondition: vector2f of position
void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
	animation->setPosition(position.x, position.y);
}

//set the x position
//precondition: double x pos
void GameObject::setX(double x)
{
	position.x = x;
	animation->setPosition(x,y);
}

//set the y position
//precondition: double y post
void GameObject::setY(double y)
{
	position.y = y;
	animation->setPosition(x,y);
}

//method to move the game object
void GameObject::move(sf::Vector2f velocity)
{
	animation->move(velocity);
}