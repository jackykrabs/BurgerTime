#pragma once
#include "Structure.h"

class Floor : public Structure
{
public:
	Floor();
	Floor(Floor*, Floor*);
	~Floor();

	Floor* getLeft(){ return lSide; }
	Floor* getRight(){ return rSide; }
	void setLeft(Floor* f){ lSide = f; };
	void setRight(Floor* f){ rSide = f; };
private: 
	int length;

	Floor* lSide;
	Floor* rSide;
};

