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
private:
	sf::RenderWindow gameWindow;
	Level* level;
	int levelNumber;
	int lives;
	int score;

};

