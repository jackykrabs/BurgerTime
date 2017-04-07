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
	
private:
	bool stunned;
	int stunnedTimer;
};

