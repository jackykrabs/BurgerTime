// GameObject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

GameObject::GameObject()
{
<<<<<<< HEAD
	animation = new Animation("pepper", "walking", 30);
	timer = 0;
=======
	GameObject("sasser.jpg");
}

GameObject::GameObject(std::string fileName)
{
>>>>>>> origin/master
	sf::Image myImage;
	myImage.loadFromFile("images//"+fileName);
	myTexture.loadFromImage(myImage);
	mySprite.setTexture(myTexture);
	mySprite.setOrigin(mySprite.getTextureRect().width / 2, mySprite.getTextureRect().height / 2);
	mySprite.scale(5, 5);
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
		animation->setFrame(animation->getFrame() + 1);
	if (animation->getMaxFrame() == animation->getFrame())
		animation->setFrame(animation->getMinFrame());

	//iterate timer
	timer++;
}

//set the overall position
//precondition: vector2f of position
void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
}

//set the x position
//precondition: double x pos
void GameObject::setX(double x)
{
	position.x = x;
	animation->setPosition(position);
}

//set the y position
//precondition: double y post
void GameObject::setY(double y)
{
	position.y = y;
	animation->setPosition(position);
}