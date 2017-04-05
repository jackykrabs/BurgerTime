#include "stdafx.h"
#include "Level.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics\Text.hpp>
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
	this->score = score;
	buildLevel();
	player->setShots(200);

	//set up the display information
	font.loadFromFile("Pixeled.ttf");

	shotsLabel.setFont(font);
	shotsLabel.setPosition(400, 50);
	shotsLabel.setString("Shots: " + std::to_string(player->getShots()));

	scoreLabel.setFont(font);
	scoreLabel.setPosition(750, 50);
	scoreLabel.setString("Score: " + std::to_string(score));

	levelLabel.setFont(font);
	levelLabel.setPosition(100, 50);
	levelLabel.setString("Level: " + std::to_string(levelNumber));

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

			allObjects.clear();
			allObjects = gameObjects;
			allObjects.push_back(player);

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
	//update label
	scoreLabel.setString("Score: " + std::to_string(score));
	shotsLabel.setString("Shots: " + std::to_string(player->getShots()));

	//player logic
	player->move(player->getVelocity());
	player->step();

	collisionCheck(allObjects);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->move(gameObjects.at(i)->getVelocity());
		gameObjects.at(i)->step();

		if (Enemy* e = dynamic_cast<Enemy*>(gameObjects.at(i)))
		{
			if (e->getTimer() % 60 == 0)
				e->findPlayer(player);
		}
	}
	//method to kill off all gameobjects that need killing off
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getDeathTimer() == gameObjects.at(i)->getDeathCountDown()) 
		{
			delete gameObjects.at(i);
			gameObjects.erase(gameObjects.begin() + i);
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
			player->setvY(5);
			if (player->getAction() != "climbing")
			{
				player->setAction("climbing");
				player->processAction();
			}
			break;
		case sf::Keyboard::Up:
			player->setvY(-5);
			if (player->getAction() != "climbing")
			{
				player->setAction("climbing");
				player->processAction();
			}
			break;
		case sf::Keyboard::Left:
			if (player->getAction() != "walking")
			{
				player->setAction("walking");
				player->processAction();
			}
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
				player->processAction();
			}
			player->setvX(5);
			if (player->getDirection() == 0)
			{
				player->flip();
				player->setDirection(1);
			}
			break;
		case sf::Keyboard::Return:
			if (player->getAction() != "throwing")
			{
				player->setAction("throwing");
				player->processAction();
				if (player->getShots() != 0)
				{
					gameObjects.push_back(new PepperShot(player));
					player->incrimentShots(-1);
					score += 50;
				}
			}
			break;

		//temp/fun methods to spawn in a bunch of enemies
		case sf::Keyboard::H:
			gameObjects.push_back(new Enemy("hotdog"));
			break;
		case sf::Keyboard::P:
			gameObjects.push_back(new Enemy("pickle"));
			break;
		case sf::Keyboard::E:
			gameObjects.push_back(new Enemy("egg"));
		}
		break;

	//make it so the gameobject stops moving when the key is released
	case sf::Event::KeyReleased:
		player->setvX(0);
		player->setvY(0);
		if (player->getAction() == "climbing")
		{
			player->setAction("still");
			player->processAction();
		}
		else if (player->getAction() != "stillSide")
		{
			player->setAction("stillSide");
			player->processAction();
		}
		break;
	}
}

//draw the objects in the level
//no preconditions or postconditions
void Level::drawObjects()
{
	window->clear();
	window->draw(shotsLabel);
	window->draw(levelLabel);
	window->draw(scoreLabel);
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


void Level::collisionCheck(std::vector<GameObject*> l)
{
	for (int x = 0; x < l.size(); x++)
	{
		for (int n = 0; n < l.size(); n++)
		{

			if (x != n && //Comparison to itself would yield a collision
				overlap(l[x], l[n]) == true)
			{
				if (Player* p = dynamic_cast<Player*> (l[x]))
				{
					if (Item* i = dynamic_cast<Item*> (l[n]))
						i->setToDie(true);
				}
				if (PepperShot* p = dynamic_cast<PepperShot*>(l[x]))
				{
					if (Enemy* e = dynamic_cast<Enemy*>(l[n]))
						e->setToDie(true);
				}
			}

		}
	}

	return;
}


bool Level::overlap(GameObject * r1, GameObject * r2)
{
	if ((r1->getPosition().x - (r1->getAnimationSprite()->getLocalBounds().width / 2)) < (r2->getPosition().x + (r2->getAnimationSprite()->getLocalBounds().width / 2)) && //If r1 left edge to left of r2 right edge
		(r1->getPosition().x + (r1->getAnimationSprite()->getLocalBounds().width / 2)) > (r2->getPosition().x - (r2->getAnimationSprite()->getLocalBounds().width / 2)) && //If r1 right edge to left of r2 left edge
		(r1->getPosition().y - (r1->getAnimationSprite()->getLocalBounds().height / 2)) < (r2->getPosition().y + (r2->getAnimationSprite()->getLocalBounds().height / 2)) && //If r1 top above r2 bottom
		(r1->getPosition().y + (r1->getAnimationSprite()->getLocalBounds().height / 2)) > (r2->getPosition().y - (r2->getAnimationSprite()->getLocalBounds().height / 2))) //If r1 bottom below r2 top
	{
		return true;
	}
	else
		return false;
}