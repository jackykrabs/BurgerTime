#pragma once
#include "GameObject.h"

class PepperShot : public GameObject
{
public:
	PepperShot(GameObject*);
	PepperShot(GameObject*, bool);
	~PepperShot();
	virtual void step();
private:
	void initializePosition(bool, GameObject*);
};