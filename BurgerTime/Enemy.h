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
};

