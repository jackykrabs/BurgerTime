#include "stdafx.h"
#include "Level.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <string.h>
#include "Item.h"
#include "Ingredient.h"
#include "Ladder.h"
#include "Floor.h"
#include "Enemy.h"
#include "PepperShot.h"

Level::Level(int levelNumber, int lives, int score, sf::RenderWindow *window)
{
	this->window = window;
	this->levelNumber = levelNumber;
	buildLevel();
	player = new Player();

	for (int i = 0; i < 5; i++)
	{
		gameObjects.push_back(new Floor());
		gameObjects.at(i)->setPosition(sf::Vector2f(500 + 56 * i, 500));
	}
	for (int i = 5; i < 10; i++)
	{
		gameObjects.push_back(new Ladder());
		gameObjects.at(i)->setPosition(sf::Vector2f(570, 100 + i * 75));
	}
	gameObjects.push_back(new Item("ice_cream_cone"));
	gameObjects.at(10)->setPosition(sf::Vector2f(710, 477));
	gameObjects.push_back(new Item("fries"));
	gameObjects.at(11)->setPosition(sf::Vector2f(660, 477));
	gameObjects.push_back(new Item("coffee"));
	gameObjects.at(12)->setPosition(sf::Vector2f(610, 477));
	gameObjects.push_back(new Enemy("egg"));
	gameObjects.at(13)->setPosition(sf::Vector2f(550, 477)); 
	gameObjects.push_back(new Enemy("hotdog"));
	gameObjects.at(14)->setPosition(sf::Vector2f(600, 477));
	gameObjects.push_back(new Enemy("pickle"));
	gameObjects.at(15)->setPosition(sf::Vector2f(650, 477));

}

Level::~Level()
{
}

//holds the gameloop for the level
//no preconditions or post conditions
void Level::play()
{

	while (window->isOpen() && levelComplete != true)
	{
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
			drawObjects();
			
			gameClock.restart();
		}
	}
}

//handles all the logic of the game (moving game objects, etc.)
//no preconditions or postconditions
void Level::gameLogic()
{
	player->move(player->getVelocity());
	//game logic goes here
	player->step();

	std::cout << gameObjects.size() << std::endl;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->move(gameObjects.at(i)->getVelocity());
		gameObjects.at(i)->step();
		if (PepperShot* p = dynamic_cast<PepperShot*>(gameObjects.at(i)))
		{
			//check if the pepper shot has been on the screen for 20 'hits'
			if (p->getTimer() == 20)
			{
				delete gameObjects.at(i);
				gameObjects.erase(gameObjects.begin() + i);
			}
		}
	}
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
			player->setvY(5);
			if (player->getAction() != "climbing")
			{
				player->setAction("climbing");
				player->processName();
			}
			break;
		case sf::Keyboard::Up:
			std::cout << "Up was pressed" << std::endl;
			player->setvY(-5);
			if (player->getAction() != "climbing")
			{
				player->setAction("climbing");
				player->processName();
			}
			break;
		case sf::Keyboard::Left:
			if (player->getAction() != "walking")
			{
				player->setAction("walking");
				player->processName();
			}
			std::cout << "Left was pressed" << std::endl;
			player->setvX(-5);
			if (player->getDirection() == 1)
			{
				player->flip();
				player->setDirection(0);
			}
			break;
		case sf::Keyboard::Right:
			if (player->getAction() != "walking")
			{
				player->setAction("walking");
				player->processName();
			}
			std::cout << "Right was pressed" << std::endl;
			player->setvX(5);
			if (player->getDirection() == 0)
			{
				player->flip();
				player->setDirection(1);
			}
			break;
		case sf::Keyboard::Return:
			std::cout << "Pepper shot!" << std::endl;
			if (player->getAction() != "throwing")
			{
				player->setAction("throwing");
				player->processName();
			}
			gameObjects.push_back(new PepperShot(player));
	
			break;
		}
		break;

	//make it so the gameobject stops moving when the key is released
	case sf::Event::KeyReleased:
		player->setvX(0);
		player->setvY(0);
		if (player->getAction() != "still")
		{
			player->setAction("still");
			player->processName();
		}
		break;
	}
}

//draw the objects in the level
//no preconditions or postconditions
void Level::drawObjects()
{
	window->clear();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		window->draw(*gameObjects.at(i)->getAnimationSprite());
	}
	window->draw(*player->getAnimationSprite());
	window->display();
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