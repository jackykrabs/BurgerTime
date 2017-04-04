#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void processAction();

	//getters and setters
	std::string getAction() { return action; }
	void setAction(std::string action) { this->action = action; }

	int getShots() { return pepperShots; }
	void setShots(int shots) { pepperShots = shots; }
	void incrimentShots(int shots) { pepperShots += shots; }

private:
	std::string action;
	int pepperShots;

};

