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

	//set up the display information
	font.loadFromFile("Pixeled.ttf");
	scoreLabel.setFont(font);
	scoreLabel.setPosition(750, 50);
	scoreLabel.setString("Score: " + std::to_string(score));
	levelLabel.setFont(font);
	levelLabel.setPosition(100, 50);
	levelLabel.setString("Level: " + std::to_string(levelNumber));

	buildLevel();
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
	std::cout << "ooga booga" << std::endl;
	//update label
	scoreLabel.setString("Score: " + std::to_string(score));

	//player logic
	player->move(player->getVelocity());
	player->step();

	quadTree(0, 0, window->getSize().x, window->getSize().y, allObjects);

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
			}
			gameObjects.push_back(new PepperShot(player));
			score += 50;
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

void Level::quadTree(int x_, int y_, int xLen, int yLen, std::vector<GameObject*> l)
{
	bool sideQuads[4]; // Used to check which quadrants are on screen edge

	//Color List
	sf::Color cList[6] =
	{
		sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan,
		sf::Color::Red, sf::Color::Blue, sf::Color::Magenta
	};

	std::vector<GameObject*> quad[4];
	//std::vector<sf::Vector2i*> qDir[4];
	//int quadCoord[4][2];

	//quadCoord[0][x] = xLength / 2; quadCoord[0][y] = yLength / 2;
	sf::RectangleShape xRekt(sf::Vector2f(xLen, 1));
	sf::RectangleShape yRekt(sf::Vector2f(1, yLen));

	xRekt.setOrigin(xLen / 2, .5); yRekt.setOrigin(.5, yLen / 2);

	xRekt.setPosition(x_ + (xLen / 2), y_ + (yLen / 2)); yRekt.setPosition(x_ + (xLen / 2), y_ + (yLen / 2));

	window->draw(xRekt); window->draw(yRekt);


	for (int i = 0; i < l.size(); i++)
	{
		//Quadrant 1
		if ((l[i]->getPosition().x) >(x_ + (xLen / 2)) && (l[i]->getPosition().y) < (y_ + (yLen / 2)))
		{
			quad[0].push_back(l[i]);
		}
		//Quadrant 2
		else if ((l[i]->getPosition().x) < (x_ + (xLen / 2)) && (l[i]->getPosition().y) < (y_ + (yLen / 2)))
		{
			quad[1].push_back(l[i]);
		}
		//Quadrant 3
		else if ((l[i]->getPosition().x) < (x_ + (xLen / 2)) && (l[i]->getPosition().y) > (y_ + (yLen / 2)))
		{
			quad[2].push_back(l[i]);
		}
		//Quadrant 4
		else if ((l[i]->getPosition().x) > (x_ + (xLen / 2)) && (l[i]->getPosition().y) > (y_ + (yLen / 2)))
		{
			quad[3].push_back(l[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (quad[i].size() > 4)
		{
			//std::cout << "QUADSELECTED: " << i << std::endl << std::endl;

			if (i == 0)
			{
				quadTree(x_ + (xLen / 2), y_, xLen / 2, yLen / 2, quad[0]);
			}
			else if (i == 1)
			{
				quadTree(x_, y_, xLen / 2, yLen / 2, quad[1]);
			}
			else if (i == 2)
			{
				quadTree(x_, y_ + (yLen / 2), xLen / 2, yLen / 2, quad[2]);
			}
			else if (i == 3)
			{
				quadTree(x_ + (xLen / 2), y_ + (yLen / 2), xLen / 2, yLen / 2, quad[3]);
			}
		}
	}

	for (int x = 0; x < 4; x++)
	{

		if (quad[x].size() > 1 && quad[x].size() < 4)
		{
			for (int n = 0; n < quad[x].size(); n++)
			{
				for (int i = 0; i < quad[x].size(); i++)
				{

					if (i != n && //Comparison to itself would yield a collision
						overlap(quad[x][n], quad[x][i]) == true)
					{
						if (PepperShot* p = dynamic_cast<PepperShot*>(quad[x][n]))
						{
							quad[x][i]->setToDie(true);
						}
						break;
					}

				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
		sideQuads[i] = false;

	//Constraints touch left side -> quadrant 2 and 3 on screen edge
	if (x_ == 0)
	{
		sideQuads[1] = true; sideQuads[2] = true;
	}
	//Constraints touch bottom -> quadrant 1 and 2 on screen edge
	if (y_ == 0)
	{
		sideQuads[0] = true; sideQuads[1] = true;
	}
	//Constraints touch right side -> quadrant 1 and 4 on screen edge
	if (xLen + x_ == window->getSize().x)
	{
		sideQuads[0] = true; sideQuads[3] = true;
	}
	//Constraints touch bottom -> quadrant 3 and 4 on screen edge
	if (yLen + y_ == window->getSize().y)
	{
		sideQuads[2] = true; sideQuads[3] = true;
	}

	for (int x = 0; x < 4; x++)
	{

		if (sideQuads[x] == true)
		{
			//std::cout << "Quadrant: " << x << std::endl;
			for (int i = 0; i < quad[x].size(); i++)
			{
				l[i]->getAnimationSprite()->getLocalBounds().width;
				//If right side is to right of window's right
				if (quad[x][i]->getPosition().x + (l[i]->getAnimationSprite()->getLocalBounds().width / 2) >= window->getSize().x)
				{
					quad[x][i]->setPosition(sf::Vector2f(quad[x][i]->getPosition().x - (quad[x][i]->getPosition().x + (l[i]->getAnimationSprite()->getLocalBounds().width / 2) - window->getSize().x), quad[x][i]->getPosition().y));

				}
				//If left side is to left of window's left
				if (quad[x][i]->getPosition().x - (quad[x][i]->getAnimationSprite()->getLocalBounds().width / 2) <= 0)
				{
					quad[x][i]->setPosition(sf::Vector2f(0 + (quad[x][i]->getAnimationSprite()->getLocalBounds().width / 2), quad[x][i]->getPosition().y));

				}
				//If bottom is below window bottom
				if (quad[x][i]->getPosition().y + (quad[x][i]->getAnimationSprite()->getLocalBounds().height / 2) >= window->getSize().y)
				{
					quad[x][i]->setPosition(sf::Vector2f(quad[x][i]->getPosition().x, quad[x][i]->getPosition().y - (quad[x][i]->getPosition().y + (quad[x][i]->getAnimationSprite()->getScale().y / 2) - window->getSize().y)));

				}
				//If top is above window top
				if (quad[x][i]->getPosition().y - (quad[x][i]->getAnimationSprite()->getScale().y / 2) <= 0)
				{
					quad[x][i]->setPosition(sf::Vector2f(quad[x][i]->getPosition().x, 0 + (quad[x][i]->getAnimationSprite()->getScale().y / 2)));

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