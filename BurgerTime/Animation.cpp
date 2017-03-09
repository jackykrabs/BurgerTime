#include "stdafx.h"
#include "Animation.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

Animation::Animation(std::string name, std::string action, int animationSpeed, sf::Vector2f position)
{
	isFlipped = false;
	direction = 0;
	texture = new sf::Texture();
	sprite = new sf::Sprite();
	this->name = name;
	this->action = action;
	this->animationSpeed = animationSpeed;
	processName();
	loadImages();
	loadTexture();
	sprite->setTexture(*texture);
	sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
	this->position = position;
}


Animation::~Animation()
{
}

//method to set the proper min and max frame based on the animation name
void Animation::processName()
{
	if (action == "walking")
	{
		minFrame = 5;
		maxFrame = 6;
	}
	else if (action == "still")
	{
		minFrame = 0;
		maxFrame = 0;
	}
	else if (action == "throwing")
	{
		minFrame = 11;
		maxFrame = 11;
	}
	else if (action == "climbing")
	{
		minFrame = 12;
		maxFrame = 13;
	}
	frame = minFrame;
}

//method to load the images into the images vector (just from the name)
void Animation::loadImages()
{
	if (name != "coffee")
	{
		for (int i = 1; i <= 14; i++)
		{
			sf::Image* temp = new sf::Image();
			std::string filePath = "images\\" + name + "-" + std::to_string(i) + ".png";
			temp->loadFromFile(filePath);
			images.push_back(temp);
		}
	}
	else{
		sf::Image* temp = new sf::Image();
		temp->loadFromFile("images\\coffee.png");
		images.push_back(temp);
	}
}

//method to load the texture
void Animation::loadTexture()
{
	int width = images.at(frame)->getSize().x;
	int height = images.at(frame)->getSize().y;
	texture->loadFromImage(*images.at(frame));
	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(0, 0, width, height));
	sprite->setPosition(position);
}

//set position
void Animation::setPosition(double x, double y)
{
	sprite->setPosition((float)x,(float) y);
}

//method to set the scale of the object
void Animation::setScale(sf::Vector2f scale)
{
	sprite->setScale(scale);
}

//method to move the object
void Animation::move(sf::Vector2f velocity)
{
	sprite->move(velocity);
	position.x += velocity.x;
	position.y += velocity.y;
}

//method to set frame and update sprite
void Animation::setFrame(int frame)
{
	this->frame = frame;
	loadTexture();
}

//method to flip GO
void Animation::flip()
{
	std::cout << "Flipping..." << std::endl;
	sprite->setScale(sprite->getScale().x*-1, sprite->getScale().y);
}