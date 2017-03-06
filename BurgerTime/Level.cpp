#include "stdafx.h"
#include "Level.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <string.h>

Level::Level(int levelNumber, int lives, int score, sf::RenderWindow *window)
{
	this->window = window;
	this->levelNumber = levelNumber;
	buildLevel();
	myGO = new GameObject("pepper-6.png");
}

Level::~Level()
{
}

//holds the gameloop for the level
//no preconditions or post conditions
void Level::play()
{
<<<<<<< HEAD
	myGO.setX(50);
	myGO.setY(50);
=======
	myGO->mySprite.setPosition(50, 50);
>>>>>>> origin/master
	int counter = 0;
	sf::Clock tempClock;
	sf::Time tempTime;
	while (window->isOpen() && levelComplete != true)
	{
		tempTime = tempClock.getElapsedTime();
		gameTime = gameClock.getElapsedTime();

		//control the game to be limited to about 60 fps
		if (gameTime.asMilliseconds() >= 17)
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				handleEvents(event);
			}
			gameLogic();

			window->clear();
<<<<<<< HEAD
			window->draw(myGO.getAnimationSprite());
=======
			window->draw(myGO->mySprite);
>>>>>>> origin/master
			window->display();
			gameClock.restart();
			counter++;
		}
		if (tempTime.asMilliseconds() >= 1000)
		{
			tempClock.restart();
			std::cout << counter << std::endl;
			counter = 0;
		}
	}
}

//handles all the logic of the game (moving game objects, etc.)
//no preconditions or postconditions
void Level::gameLogic()
{
	myGO->mySprite.move(myGO->getVelocity());
	//game logic goes here
}

//handle the events (key input, close screen, etc)
//preconditions: current event
void Level::handleEvents(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Down:
			std::cout << "Down was pressed" << std::endl;
			myGO->setvY(5);
			break;
		case sf::Keyboard::Up:
			std::cout << "Up was pressed" << std::endl;
			myGO->setvY(-5);
			break;
		case sf::Keyboard::Left:
			//levelComplete = true;
			std::cout << "Left was pressed" << std::endl;
			myGO->setvX(-5);
			break;
		case sf::Keyboard::Right:
			std::cout << "Right was pressed" << std::endl;
			myGO->setvX(5);
			myGO->mySprite.scale(-1, 1);
			break;
		case sf::Keyboard::Return:
			std::cout << "Pepper shot!" << std::endl;
			myGO->updateClipart();
			break;
		}
		break;

	//make it so the gameobject stops moving when the key is released
	case sf::Event::KeyReleased:
		myGO->setvX(0);
		myGO->setvY(0);
		break;
	}
}

//build the level, based off the current level number (1-6)
//preconditions: level number is set (should be set in constructor)
void Level::buildLevel()
{
	switch (levelNumber)
	{
	case 1:
		buildLevelOne();
		break;
	case 2:
		buildLevelTwo();
		break;
	case 3:
		buildLevelThree();
		break;
	case 4:
		buildLevelFour();
		break;
	case 5:
		buildLevelFive();
		break;
	case 6:
		buildLevelSix();
		break;
	}

	return;
}

//build the first level
//no preconditions/postconditions
void Level::buildLevelOne()
{
	std::cout << "level one" << std::endl;
}

//build the second level
//no preconditions/postconditions
void Level::buildLevelTwo()
{

}

//build the third level
//no preconditions/postconditions
void Level::buildLevelThree()
{

}

//build the fourth level
//no preconditions/postconditions
void Level::buildLevelFour()
{

}

//build the fifth level
//no preconditions/postconditions
void Level::buildLevelFive()
{

}

//build the sixth level
//no preconditions/postconditions
void Level::buildLevelSix()
{

}