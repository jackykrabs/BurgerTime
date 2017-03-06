#include "stdafx.h"
#include "Animation.h"
#include <iostream>
#include <string>
#include <vector>

Animation::Animation(std::string name, std::string action, int animationSpeed)
{
	this->name = name;
	this->action = action;
	this->animationSpeed = animationSpeed;
	loadImages();
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
		maxFrame = 7;
	}
}

//method to load the images into the images vector (just from the name)
void Animation::loadImages()
{
	for (int i = 1; i <= 13; i++)
	{
		sf::Image* temp = new sf::Image();
		std::string filePath = "images\\" + name + "-" + std::to_string(i) + ".png";
		temp->loadFromFile(filePath);
		images.push_back(temp);
	}
}

//method to load the texture
void Animation::loadTexture()
{

}
