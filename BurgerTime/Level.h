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
	int getScore() { return score; }
	int getLives() { return lives; }
	void play();

private:
	int pauseBuffer;
	bool paused;
	int lives;
	int score;
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

	int buildFloor(int, int, int, int);
	int buildLadder(int, int, int, int);
	
	void reset();
	void handleEvents(sf::Event);
	void gameLogic();
	void drawObjects();
	GameObject* gridLock(sf::Keyboard::Key*);//Locks Character to level platforms
	sf::Clock gameClock;
	sf::Time gameTime;

	void collisionCheck(std::vector<GameObject*>);
	bool overlap(GameObject *, GameObject *);

	sf::Keyboard::Key dirLock;
	sf::Font font;
	sf::Text livesLabel;
	sf::Text shotsLabel;
	sf::Text scoreLabel;
	sf::Text levelLabel;
	//test gameobject
	Player* player;
	std::vector <GameObject*> gameObjects;
	std::vector <GameObject*> allObjects;
};

