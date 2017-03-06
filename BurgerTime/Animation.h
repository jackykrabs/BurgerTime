#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <vector>

class Animation
{
public:
	Animation(std::string, std::string, int);
	void changeName(std::string);
	void setPosition(sf::Vector2f position) { this->position = position; }
	
	//getters and setters
	int getAnimationSpeed() { return animationSpeed;  }
	void setAnimationSpeed(int animationSpeed) { this->animationSpeed = animationSpeed; }
	
	int getFrame() { return frame; }
	void setFrame(int frame) { this->frame = frame; }

	int getMaxFrame() { return maxFrame; }
	void setMaxFrame(int maxFrame) { this->maxFrame = maxFrame; }

	int getMinFrame() { return minFrame; }
	void setMinFrame(int minFrame) { this->minFrame = minFrame; }

	sf::Sprite getSprite() { return sprite; }

	~Animation();
private:
	void loadTexture(); // TODO: MAKE THIS METHOD GREAT AGAIN
	void processName();
	void loadImages();
	int animationSpeed;
	int frame;
	int minFrame;
	int maxFrame;
	std::string name;
	std::string action;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<sf::Image*> images;
};

