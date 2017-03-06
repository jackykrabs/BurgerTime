// BurgerTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameState.h"

int main()
{
	GameState myGameState;
	
	for (int i = 0; i < 10; i ++)
		myGameState.playLevel();

	return 0;
}