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
#include "Sound.h"
#include "PepperShot.h"
#include <stdlib.h>

Level::Level(int levelNumber, int lives, int score, sf::RenderWindow *window)
{
	dirLock = sf::Keyboard::Key::Unknown;
	this->window = window;
	this->levelNumber = levelNumber;
	this->score = score;
	this->lives = lives;
	player = new Player();
	buildLevel();
	player->setShots(5 );
	window->setFramerateLimit(60);

	paused = false;
	pauseBuffer = 0;

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
	while (window->isOpen() && levelComplete != true && lives != 0)
	{
		gameTime = gameClock.getElapsedTime();

		//control the game to be limited to about 60 fps
			sf::Event event;
			if (!paused)
			{
				while (window->pollEvent(event))
				{
					handleEvents(event);
				}
			}

			allObjects.clear();
			allObjects = gameObjects;
			allObjects.push_back(player);

			gameLogic();
			drawObjects();

			gameClock.restart();

			if (paused)
				pauseBuffer++;
			if (pauseBuffer == 120)
			{
				paused = false;
				pauseBuffer = 0;
				reset();
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
	if (!paused)
		player->move(player->getVelocity());
	player->step();

	collisionCheck(allObjects);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (!paused)
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
		lives = 0;
		break;
	case sf::Event::KeyPressed:
		if (dirLock == sf::Keyboard::Key::Unknown)
			dirLock = event.key.code;

		//if ()
		/*If Gridlock returns a nullptr, it means that the player is colliding with both
		a floor and a ladder and a keypress must determine where to go*/
		if (gridLock(nullptr) == nullptr)
		{
			gridLock(&event.key.code);
		}

		switch (event.key.code)
		{
		case sf::Keyboard::Down:
			if (dirLock == event.key.code && player->getlLock() == gridLock(nullptr))//If currently locked to ladder
			{
				player->setvY(5);
				player->setClimbingUp(false);
				if (player->getAction() != "climbing")
				{
					player->setAction("climbing");
					player->processAction();
					player->setClimbing(true);
				}
			}
			break;
		case sf::Keyboard::Up:
			if (dirLock == event.key.code && player->getlLock() == gridLock(nullptr))//If currently locked to ladder
			{
				player->setvY(-5);
				player->setClimbingUp(true);
				if (player->getAction() != "climbing")
				{
					player->setAction("climbing");
					player->processAction();
					player->setClimbing(true);
				}
			}
			break;
		case sf::Keyboard::Left:
			if (dirLock == event.key.code && player->getfLock() == gridLock(nullptr))//If currently locked to floor
			{
				if (player->getAction() != "walking")
				{
					player->setAction("walking");
					player->processAction();
					player->setClimbing(false);
				}
				player->setvX(-5);
				if (player->getDirection() != 0)
				{
					player->flip();
					player->setDirection(0);
				}
			}
			break;
		case sf::Keyboard::Right:
			if (dirLock == event.key.code && player->getfLock() == gridLock(nullptr))//If currently locked to floor
			{
				if (player->getAction() != "walking")
				{
					player->setAction("walking");
					player->processAction();
					player->setClimbing(false);
				}
				player->setvX(5);
				if (player->getDirection() != 1)
				{
					player->flip();
					player->setDirection(1);
				}
			}
			break;
			//todo: make it so he can shoot pepper up
		case sf::Keyboard::Return:
			if (player->getAction() != "throwing")
			{
				player->setAction("throwing");
				player->processAction();
				if (player->getShots() != 0)
				{
					if (player->getClimbing() == false)
						gameObjects.push_back(new PepperShot(player));
					else
					{
						if (player->getClimbingUp())
							gameObjects.push_back(new PepperShot(player, true));
						else
							gameObjects.push_back(new PepperShot(player, false));
					}
					player->incrimentShots(-1);
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

		case sf::Keyboard::C:
			levelComplete = true;
		}
		break;

	//make it so the gameobject stops moving when the key is released
		case sf::Event::KeyReleased:
			if (event.key.code == dirLock)
				dirLock = sf::Keyboard::Key::Unknown;
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

	player->setfLock(nullptr); player->setlLock(nullptr); //Prevents rubber banding
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
	int step = 0;
	Floor ex;
	Ladder ex2;
	int offset = ((window->getSize().x - (13 * 75)) /2);
	int fComp = ex.getAnimationSprite()->getGlobalBounds().height;

	//1st Floor (Step 0-16)
	step = buildFloor(step, (4 * 3) + 5, offset, (window->getSize().y / 5));
	for (int i = 0; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	//2nd Floor (Step 17-31)
	step = buildFloor(step, 5, offset,(window->getSize().y / 5) + (2 * 75) - fComp); 
	for (int i = step - 5; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);
	
	step = buildFloor(step, 9, offset + (6 * 75), (window->getSize().y / 5) + (2 * 75)- fComp);
	for (int i = step - 9; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	//3rd Floor (Step 32-37)
	step = buildFloor(step, 5, offset + (3 * 75), (window->getSize().y / 5) + (3 * 75) - fComp);
	for (int i = step - 5; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	//4th Floor (Step 38-48)
	step = buildFloor(step, 5, offset, (window->getSize().y / 5) + (4 * 75) - fComp);
	for (int i = step - 5; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	step = buildFloor(step, 5, offset + (9 * 75), (window->getSize().y / 5) + (4 * 75) - fComp);
	for (int i = step - 5; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	//5th Floor (Step 49-58)
	step = buildFloor(step, 9, offset + (3 * 75), (window->getSize().y / 5) + (5 * 75) - fComp);
	for (int i = step - 9; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);
	
	//6th Floor (Step 59-64)
	step = buildFloor(step, 5, offset + (9 * 75), (window->getSize().y / 5) + (6 * 75) - fComp);
	for (int i = step - 5; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);

	//7th Floor (Step 65-78)
	step = buildFloor(step, (4 * 3) + 1, offset, (window->getSize().y / 5) + (7 * 75) - fComp);
	for (int i = step - 13; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);
	
	//8th Floor (Step 79-96)
	step = buildFloor(step, (4 * 3) + 5, offset, (window->getSize().y / 5) + (9 * 75) - fComp);
	for (int i = step - 17; i < step; i += 4)
		gameObjects.at(i)->getAnimationSprite()->setColor(sf::Color::Blue);
	
	//0
	step = buildLadder(step, 2, gameObjects.at(0)->getPosition().x, gameObjects.at(0)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);
	step = buildLadder(step, 5, gameObjects.at(0)->getPosition().x, gameObjects.at(32)->getPosition().y - ((fComp / 2) * 3) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) * 3 - fComp);
	
	//2 !!
	step = buildLadder(step, 5, gameObjects.at(2)->getPosition().x, gameObjects.at(17)->getPosition().y - fComp + (ex2.getAnimationSprite()->getGlobalBounds().height / 2));

	//4
	step = buildLadder(step, 9, gameObjects.at(4)->getPosition().x, gameObjects.at(0)->getPosition().y  - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);
	
	//6
	step = buildLadder(step, 3, gameObjects.at(6)->getPosition().x, gameObjects.at(0)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);

	//8
	step = buildLadder(step, 9, gameObjects.at(8)->getPosition().x, gameObjects.at(0)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);

	//10
	step = buildLadder(step, 3, gameObjects.at(10)->getPosition().x, gameObjects.at(17)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);
	//12
	step = buildLadder(step, 9, gameObjects.at(12)->getPosition().x, gameObjects.at(0)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);

	//14
	step = buildLadder(step, 5, gameObjects.at(14)->getPosition().x, gameObjects.at(32)->getPosition().y - (fComp/ 2 * 3) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) * 3 - fComp);

	//16
	step = buildLadder(step, 4, gameObjects.at(16)->getPosition().x, gameObjects.at(0)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);
	step = buildLadder(step, 3, gameObjects.at(16)->getPosition().x, gameObjects.at(59)->getPosition().y - (fComp / 2) + (ex2.getAnimationSprite()->getGlobalBounds().height / 2) - fComp);

	gameObjects.push_back(new Enemy("pickle"));
	
	gameObjects.push_back(new Item("ice_cream_cone"));
	gameObjects.at(step)->setOriginalPosition(sf::Vector2f(710, 477));
	gameObjects.push_back(new Item("fries"));
	gameObjects.at(step + 1)->setOriginalPosition(sf::Vector2f(660, 477));
	gameObjects.push_back(new Item("coffee"));
	gameObjects.at(step + 2)->setOriginalPosition(sf::Vector2f(610, 477));
	gameObjects.push_back(new Enemy("egg"));
	gameObjects.at(step + 3)->setOriginalPosition(sf::Vector2f(550, 477));
	gameObjects.push_back(new Enemy("hotdog"));
	gameObjects.at(step + 4)->setOriginalPosition(sf::Vector2f(600, 477));
	gameObjects.push_back(new Enemy("pickle"));
	gameObjects.at(step + 5)->setOriginalPosition(sf::Vector2f(650, 477));
}


int Level::buildFloor(int step, int it, int x_, int y_)
{
	for (int i = step; i < step + it; i++)
	{
		gameObjects.push_back(new Floor());
		gameObjects.at(i)->setPosition(sf::Vector2f(x_ + (56 * (i - step)), y_));
	}
	for (int i = step; i < step + it; i++)
	{
		dynamic_cast<Floor*> (gameObjects.at(i))->setLeft(dynamic_cast<Floor*> (gameObjects.at(step)));
		dynamic_cast<Floor*> (gameObjects.at(i))->setRight(dynamic_cast<Floor*> (gameObjects.at(step + it - 1)));
	}

	return step + it;
}


int Level::buildLadder(int step, int it, int x_, int y_)
{
	for (int i = step; i < step + it; i++)
	{
		gameObjects.push_back(new Ladder());
		gameObjects.at(i)->setPosition(sf::Vector2f(x_, y_ + ((i - step) * 75)));
	}
	for (int i = step; i < step + it; i++)
	{
		dynamic_cast<Ladder*> (gameObjects.at(i))->setTop(dynamic_cast<Ladder*> (gameObjects.at(step)));
		dynamic_cast<Ladder*> (gameObjects.at(i))->setBot(dynamic_cast<Ladder*> (gameObjects.at(step + it - 1)));
	}

	return step + it;
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
		if (l[x] == dynamic_cast<Player*>(l[x]) || l[x] == dynamic_cast<Enemy*>(l[x]) || l[x] == dynamic_cast<PepperShot*>(l[x]))
		{
			for (int n = 0; n < l.size(); n++)
			{
				if (x != n && //Comparison to itself would yield a collision
					overlap(l[x], l[n]) == true)
				{
					if (Enemy* e = dynamic_cast<Enemy*> (l[x]))
					{
						if (l[n] == dynamic_cast<Ladder*> (l[n]))//If colliding with ladderr
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
							if (dirLock == sf::Keyboard::Key::Up && p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getTop() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) <= (p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) + 5))
							{
								p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) - (p->getAnimationSprite()->getGlobalBounds().height / 4)));
							}
							//If moving past bottom of ladder
							else if (dirLock == sf::Keyboard::Key::Down && p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getBot() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) >= (p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2)))
							{
								p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
							}
						}

						if (l[n] == dynamic_cast<Floor*> (l[n]))//If colliding with floor
						{
							p->setfLock(l[n]);

							//If moving past left side
							if (dirLock == sf::Keyboard::Left && p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getLeft() && (p->getPosition().x - (p->getAnimationSprite()->getGlobalBounds().width / 2)) <= (p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
							{
								p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x - (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) + (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
							}
							//If moving past right side
							else if (dirLock == sf::Keyboard::Key::Right && p->getfLock() == dynamic_cast<Floor*>(p->getfLock())->getRight() && (p->getPosition().x + (p->getAnimationSprite()->getGlobalBounds().width / 2)) >= (p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2)))
							{
								p->setPosition(sf::Vector2f(p->getfLock()->getPosition().x + (p->getfLock()->getAnimationSprite()->getGlobalBounds().width / 2) - (p->getAnimationSprite()->getGlobalBounds().width / 2), p->getPosition().y));
							}
						}

						if (Item* i = dynamic_cast<Item*> (l[n])){
							i->setToDie(true);
							player->incrimentShots(1); 
						}

						//DEATH TO PEPPER!!!!11
						if (Enemy* e = dynamic_cast<Enemy*>(l[n]))
						{
							if (e->getStunned() == false && e->getToDie() == false && !paused)
							{
								p->setlLock(nullptr);
								p->setfLock(nullptr); //Wipes gridlock for movement readjustment after respawning
								paused = true;
								player->setAction("dying");
								player->processAction();
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
							if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getTop() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) <= (p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) + 2))
							{
								p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y - (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) - 2));
							}
							//If moving past bottom of ladder
							else if (p->getlLock() == dynamic_cast<Ladder*>(p->getlLock())->getBot() && (p->getPosition().y + (p->getAnimationSprite()->getGlobalBounds().height / 2)) >= (p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) + 3))
							{
								p->setPosition(sf::Vector2f(p->getlLock()->getPosition().x, p->getlLock()->getPosition().y + (p->getlLock()->getAnimationSprite()->getGlobalBounds().height / 2) - (p->getAnimationSprite()->getGlobalBounds().height / 2)));
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
	}

	return;
}


bool Level::overlap(GameObject * r1, GameObject * r2)
{
	int legsComp = 2;
	int lComp = 1;

	if ((r1 == dynamic_cast<Player*>(r1) || r1 == dynamic_cast<Enemy*>(r1)) && (r2 == dynamic_cast<Floor*>(r2) || r2 == dynamic_cast<Ladder*>(r2)))
	{
		legsComp = 4; lComp = -1;
	}

	if ((r1->getPosition().x - (r1->getAnimationSprite()->getGlobalBounds().width / 2)) < (r2->getPosition().x + (r2->getAnimationSprite()->getGlobalBounds().width / 2)) && //If r1 left edge to left of r2 right edge
		(r1->getPosition().x + (r1->getAnimationSprite()->getGlobalBounds().width / 2)) > (r2->getPosition().x - (r2->getAnimationSprite()->getGlobalBounds().width / 2)) && //If r1 right edge to left of r2 left edge
		(r1->getPosition().y - ((r1->getAnimationSprite()->getGlobalBounds().height / legsComp) * lComp)) < (r2->getPosition().y + (r2->getAnimationSprite()->getGlobalBounds().height / 2)) && //If r1 top above r2 bottom
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
void Level::reset()
{
	lives--;
	player->setPosition(player->getOriginalPosition());
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (Enemy* e = dynamic_cast<Enemy*> (gameObjects.at(i)))
			e->setPosition(e->getOriginalPosition());
	}
	player->setAction("still");
	player->processAction();
}