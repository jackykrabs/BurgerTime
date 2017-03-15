#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

class Animation
{
public:
	Animation(std::string, std::string, int, sf::Vector2f);
	void changeName(std::string);
	//void setPosition(sf::Vector2f position) { this->position = position; }
	void setPosition(double x, double y);

	//getters and setters
	std::string getAction() { return action; }
	void setAction(std::string action) { this->action = action; }

	int getAnimationSpeed() { return animationSpeed; }
	void setAnimationSpeed(int animationSpeed) { this->animationSpeed = animationSpeed; }

	int getFrame() { return frame; }
	void setFrame(int frame);

	int getMaxFrame() { return maxFrame; }
	void setMaxFrame(int maxFrame) { this->maxFrame = maxFrame; }

	int getMinFrame() { return minFrame; }
	void setMinFrame(int minFrame) { this->minFrame = minFrame; }

	void setFlipped(bool flipped) { this->isFlipped = flipped; }

	int getDirection() { return direction; }
	void setDirection(int direction) { this->direction = direction; }

	sf::Sprite* getSprite() { return sprite; }

	void processName();
	void setScale(sf::Vector2f);
	void move(sf::Vector2f);
	void flip();
	~Animation();
private:
	bool isStillSprite(std::string); 
	void initStillSprites();
	std::vector <std::string> stillSprites;
	int direction; // 0 is left, 1 is right
	bool isFlipped;
	void loadTexture();
	void loadImages();
	int animationSpeed;
	int frame;
	int minFrame;
	int maxFrame;
	std::string name;
	std::string action;
	sf::Vector2f position;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<sf::Image*> images;
};

