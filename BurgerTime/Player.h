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

private:
	std::string action;
	

};

