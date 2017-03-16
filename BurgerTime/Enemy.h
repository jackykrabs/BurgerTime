#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy(std::string);
	~Enemy();
	virtual void step();
};

