#pragma once
#include "GameObject.h"
#include "Player.h"

class Enemy :
	public GameObject
{
public:
	void findPlayer(Player*);
	Enemy(std::string);
	~Enemy();
	virtual void step();

	//getters and setters
	void setStunned(bool stunned) { this->stunned = stunned; }
	bool getStunned(){ return stunned; }

	int getStunnedTimer() { return stunnedTimer; }
	
	void setfLock(GameObject* f) { floorLock = f; } //Sets enemy to lock to floor
	void setlLock(GameObject* l) { ladLock = l; } //Sets enemy to lock to ladder
	GameObject* getfLock() { return floorLock; }
	GameObject* getlLock() { return ladLock; }

private:
	bool stunned;
	int stunnedTimer;

	bool conflict;
	GameObject* floorLock;//Points to floor player is locked to (if it is)
	GameObject* ladLock;//Points to ladder player is locked to (if it is)

	GameObject* gridLock(bool, bool);
};

