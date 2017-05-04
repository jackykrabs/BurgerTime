// BurgerTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameState.h"
#include "Sound.h"
int main()
{
	GameState myGameState;
	Sound* mySound = new Sound("testMusic.wav", true);
	mySound->play();
	while (myGameState.getLives() != 0)
		myGameState.playLevel();

	return 0;
}