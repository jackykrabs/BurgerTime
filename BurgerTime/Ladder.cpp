#include "stdafx.h"
#include "Ladder.h"


Ladder::Ladder() : Structure("ladder")
{

}


Ladder::Ladder(Ladder* t, Ladder* b) : Structure("ladder")
{
	top = t;
	bot = b;
}


Ladder::~Ladder()
{
}
