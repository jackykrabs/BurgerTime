#pragma once
#include "Level.h"
#include <string>

class GameState
{
public:
	GameState();
	~GameState();
	void goToNextLevel();
	void playLevel();
	int getLives() { return lives; }
private:
	sf::RenderWindow gameWindow;
	Level* level;
	int levelNumber;
	int lives;
	int score;

};

