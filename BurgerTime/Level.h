#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include <vector>

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
	void drawObjects();
	sf::Clock gameClock;
	sf::Time gameTime;

	//test gameobject
	Player* player;
	std::vector <GameObject*> gameObjects;
};

