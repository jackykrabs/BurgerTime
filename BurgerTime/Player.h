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

	void setfLock(GameObject* f) { floorLock = f; } //Sets player to lock to floor
	void setlLock(GameObject* l) { ladLock = l; } //Sets player to lock to ladder
	GameObject* getfLock() { return floorLock; }
	GameObject* getlLock() { return ladLock; }
private:
	std::string action;
	int pepperShots;

	GameObject* floorLock;//Points to floor player is locked to (if it is)
	GameObject* ladLock;//Points to ladder player is locked to (if it is)
};

