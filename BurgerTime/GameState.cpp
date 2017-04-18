#include "stdafx.h"
#include "GameState.h"
#include "Level.h"
#include <iostream>

GameState::GameState()
{
	gameWindow.create(sf::VideoMode().getDesktopMode(), "Burger Time");
	levelNumber = 1;
	lives = 5;
	score = 0;
	level = new Level(levelNumber, lives, score, &gameWindow);
}


GameState::~GameState()
{
}

//iterate to the next level (loop around to level one if at level six)
//no preconditions/postconditions
void GameState::goToNextLevel()
{
	levelNumber++;
	if (levelNumber > 6)
		levelNumber = 1;
	return;
}

void GameState::playLevel()
{
	std::cout << "Level: " << levelNumber << std::endl;
	level->play();
	this->score = level->getScore();
	this->lives = level->getLives();
	goToNextLevel();
	delete level;
	level = new Level(levelNumber, lives, score, &gameWindow);
}