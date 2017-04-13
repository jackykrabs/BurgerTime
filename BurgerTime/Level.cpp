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
	this->lives = lives;

	player = new Player();
	buildLevel();
	player->setShots(200);

	//set up the display information
	font.loadFromFile("Pixeled.ttf");

	livesLabel.setFont(font);
	livesLabel.setPosition(1025, 50);
	livesLabel.setString("Lives: " + std::to_string(lives));

	shotsLabel.setFont(font);
	shotsLabel.setPosition(300, 50);
	shotsLabel.setString("Shots: " + std::to_string(player->getShots()));

	scoreLabel.setFont(font);
	scoreLabel.setPosition(650, 50);
	scoreLabel.setString("Score: " + std::to_string(score));

	levelLabel.setFont(font);
	levelLabel.setPosition(50, 50);
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
	livesLabel.setString("Lives: " + std::to_string(lives));

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

		/*If Gridlock returns a nullptr, it means that the player is colliding with both
		a floor and a ladder and a keypress must determine where to go*/
		if (gridLock(nullptr) == nullptr)
		{
			gridLock(&event.key.code);
		}

		switch (event.key.code)
		{
		case sf::Keyboard::Down:
			if (player->getlLock() == gridLock(nullptr))//If currently locked to ladder
			{
				player->setvY(5);
				if (player->getAction() != "climbing")
				{
					player->setAction("climbing");
					player->processAction();
				}
			}
			break;
		case sf::Keyboard::Up:
			if (player->getlLock() == gridLock(nullptr))//If currently locked to ladder
			{
				player->setvY(-5);
				if (player->getAction() != "climbing")
				{
					player->setAction("climbing");
					player->processAction();
				}
			}
			break;
		case sf::Keyboard::Left:
			if (player->getfLock() == gridLock(nullptr))//If currently locked to floor
			{
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
			}
			break;
		case sf::Keyboard::Right:
			if (player->getfLock() == gridLock(nullptr))//If currently locked to floor
			{
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
	window->draw(livesLabel);
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


	for (int i = 0; i < 5; i++)
	{ 
		gameObjects.push_back(new Floor());
		gameObjects.at(i)->setPosition(sf::Vector2f(500 + 56 * i, 500));
	}
	for (int i = 0; i < 5; i++)
	{
		dynamic_cast<Floor*> (gameObjects.at(i))->setLeft(dynamic_cast<Floor*> (gameObjects.at(0)));
		dynamic_cast<Floor*> (gameObjects.at(i))->setRight(dynamic_cast<Floor*> (gameObjects.at(4)));
	}
	for (int i = 5; i < 10; i++)
	{
		gameObjects.push_back(new Ladder());
		gameObjects.at(i)->setPosition(sf::Vector2f(570, 100 + i * 75));
	}
	for (int i = 5; i < 10; i++)
	{
		dynamic_cast<Ladder*> (gameObjects.at(i))->setTop(dynamic_cast<Ladder*> (gameObjects.at(5)));
		dynamic_cast<Ladder*> (gameObjects.at(i))->setBot(dynamic_cast<Ladder*> (gameObjects.at(9)));
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
				if (Enemy* e = dynamic_cast<Enemy*> (l[x]))
				{
					if (l[n] == dynamic_cast<Ladder*> (l[n]))//If colliding with ladder
						e->setlLock(l[n]);

					if (l[n] == dynamic_cast<Floor*> (l[n]))//If colliding with floor
						e->setfLock(l[n]);
				}
				//Player Collision Checks
				//--------------------------------------------------------------------------------------------------------------------------------------------
				if (Player* p = dynamic_cast<Player*> (l[x]))
				{

					if (l[n] == dynamic_cast<Ladder*> (l[n]))//If colliding with ladder
					{
						p->setlLock(l[n]);

						//If moving past top of ladder
						if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getTop() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) <= (p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) + 10))
						{
							p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
						}
						//If moving past bottom of ladder
						else if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getBot() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) >= (p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2)))
						{
							p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
						}
					}


					if (l[n] == dynamic_cast<Floor*> (l[n]))//If colliding with floor
					{
						p->setfLock(l[n]);

						//If moving past left side
						if (p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getLeft() && (p->getPosition().x - (p->getAnimationSprite()->getGlobalBounds().width / 2)) <= (p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
						{
							p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) + (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
						}
						//If moving past right side
						else if (p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getRight() && (p->getPosition().x + (p->getAnimationSprite()->getGlobalBounds().width / 2)) >= (p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
						{
							p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) - (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
						}
					}
					if (Item* i = dynamic_cast<Item*> (l[n]))
						i->setToDie(true);

					//DEATH TO PEPPER!!!!11
					if (Enemy* e = dynamic_cast<Enemy*>(l[n]))
					{
						if (e->getStunned() == false && e->getToDie() == false)
						{
							p->setlLock(nullptr); p->setfLock(nullptr); //Wipes gridlock for movement readjustment after respawning
							p->setPosition(sf::Vector2f(850, 600));
							lives--;
						}
					}
				}

				//Enemy Collision Checks
				//--------------------------------------------------------------------------------------------------------------------------------------------
				if (Enemy* p = dynamic_cast<Enemy*> (l[x]))
				{

					if (l[n] == dynamic_cast<Ladder*> (l[n]))//If colliding with ladder
					{
						p->setlLock(l[n]);

						//If moving past top of ladder
						if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getTop() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) <= (p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) + 15))
						{
							p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
						}
						//If moving past bottom of ladder
						else if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getBot() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) >= (p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2)))
						{
							p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
						}
					}


					if (l[n] == dynamic_cast<Floor*> (l[n]))//If colliding with floor
					{
						p->setfLock(l[n]);

						//If moving past left side
						if (p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getLeft() && (p->getPosition().x - (p->getAnimationSprite()->getGlobalBounds().width / 2)) <= (p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
						{
							p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) + (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
						}
						//If moving past right side
						else if (p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getRight() && (p->getPosition().x + (p->getAnimationSprite()->getGlobalBounds().width / 2)) >= (p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
						{
							p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) - (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
						}
					}
				}

				if (PepperShot* p = dynamic_cast<PepperShot*>(l[x]))
				{
					if (Enemy* e = dynamic_cast<Enemy*>(l[n]))
						e->setStunned(true);
				}
				
			}
		}

		//If right side is to right of window's right
		if (l[x]->getPosition().x + (l[x]->getAnimationSprite()->getGlobalBounds().width / 2) >= window->getSize().x)
			l[x]->setPosition(sf::Vector2f(l[x]->getPosition().x - (l[x]->getPosition().x + (l[x]->getAnimationSprite()->getGlobalBounds().width / 2) - window->getSize().x), l[x]->getPosition().y));

		//If left side is to left of window's left
		else if (l[x]->getPosition().x - (l[x]->getAnimationSprite()->getGlobalBounds().width / 2) <= 0)
			l[x]->setPosition(sf::Vector2f(0 + (l[x]->getAnimationSprite()->getGlobalBounds().width / 2), l[x]->getPosition().y));

		//If bottom is below window bottom
		if (l[x]->getPosition().y + (l[x]->getAnimationSprite()->getGlobalBounds().height / 2) >= window->getSize().y)
			l[x]->setPosition(sf::Vector2f(l[x]->getPosition().x, l[x]->getPosition().y - (l[x]->getPosition().y + (l[x]->getAnimationSprite()->getGlobalBounds().height / 2) - window->getSize().y)));

		//If top is above window top
		else if (l[x]->getPosition().y - (l[x]->getAnimationSprite()->getGlobalBounds().height / 2) <= 0)
			l[x]->setPosition(sf::Vector2f(l[x]->getPosition().x, 0 + (l[x]->getAnimationSprite()->getGlobalBounds().height / 2)));

	}

	return;
}


bool Level::overlap(GameObject * r1, GameObject * r2)
{
	if ((r1->getPosition().x - (r1->getAnimationSprite()->getGlobalBounds().width / 2)) < (r2->getPosition().x + (r2->getAnimationSprite()->getGlobalBounds().width / 2)) && //If r1 left edge to left of r2 right edge
		(r1->getPosition().x + (r1->getAnimationSprite()->getGlobalBounds().width / 2)) > (r2->getPosition().x - (r2->getAnimationSprite()->getGlobalBounds().width / 2)) && //If r1 right edge to left of r2 left edge
		(r1->getPosition().y - (r1->getAnimationSprite()->getGlobalBounds().height / 2)) < (r2->getPosition().y + (r2->getAnimationSprite()->getGlobalBounds().height / 2)) && //If r1 top above r2 bottom
		(r1->getPosition().y + (r1->getAnimationSprite()->getGlobalBounds().height / 2)) > (r2->getPosition().y - (r2->getAnimationSprite()->getGlobalBounds().height / 2))) //If r1 bottom below r2 top
	{
		return true;
	}
	else
		return false;
}


GameObject* Level::gridLock(sf::Keyboard::Key* k)
{
	Player* p = player;

	if (p->getlLock() != nullptr && p->getfLock() != nullptr) //If colliding with both ladder and floor
	{
		if (k == nullptr) //When handleEvents is checking for the above situation
		{
			return nullptr; //Let handleEvents know by returning nullptr
		}
		else
		{
			if (*k == sf::Keyboard::Down || *k == sf::Keyboard::Up) //Select ladder based on handleEvents feedback
				p->setfLock(nullptr);

			if (*k == sf::Keyboard::Left || *k == sf::Keyboard::Right) //Select floor based on handleEvents feedback
				p->setlLock(nullptr);
		}
	}

	//Ladder
	if (p->getlLock() != nullptr && p->getfLock() == nullptr)
	{
			p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getPosition().y)); //Set x to ladder's x

		return p->getlLock();
	}
	//Floor
	else if (p->getfLock() != nullptr && p->getlLock() == nullptr)
	{
		//Set player y to on top of floor
		p->setPosition(sf::Vector2f(p->getPosition().x, p->getfLock()->getPosition().y - ((p->getfLock()->getAnimationSprite()->getGlobalBounds().height / 2) + (p->getAnimationSprite()->getGlobalBounds().height / 2)) + 2));

		return p->getfLock();
	}

}