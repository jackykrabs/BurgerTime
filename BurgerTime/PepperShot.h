#pragma once
#include "GameObject.h"

class PepperShot : public GameObject
{
public:
	PepperShot(GameObject*);
	~PepperShot();
	virtual void step();
private:
};