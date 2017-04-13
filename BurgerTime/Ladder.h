#pragma once
#include "Structure.h"

//ladder is about 75 "units" tall
class Ladder : public Structure
{
public:
	Ladder();
	Ladder(Ladder*, Ladder*);
	~Ladder();

	Ladder* getTop(){ return top; }
	Ladder* getBot(){ return bot; }
	void setTop(Ladder* l){ top = l; };
	void setBot(Ladder* l){ bot = l; };

private:
	int height;

	Ladder* top;
	Ladder* bot;
};

