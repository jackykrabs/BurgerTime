#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Level
{
public:
	Level(int, int, int, sf::RenderWindow*);
	~Level();
	void play();
private:
	bool levelComplete = false;
	sf::RenderWindow* window;
	int levelNumber;
	void buildLevel();
	void buildLevelOne();
	void buildLevelTwo();
	void buildLevelThree();
	void buildLevelFour();
	void buildLevelFive();
	void buildLevelSix();
	void handleEvents(sf::Event);
	void gameLogic();
	sf::Clock gameClock;
	sf::Time gameTime;

	//test gameobject
	GameObject* myGO;
};

