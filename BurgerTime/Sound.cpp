#include "stdafx.h"
#include "Sound.h"
#include <iostream>

using namespace std;


Sound::Sound()
{
}

Sound::Sound(string fileName, bool temp)
{
	if (music)
	{
		music = temp;
		if (!gameMusic.openFromFile("Main_Theme.wav"))
			cout << "error opening music" << endl;
	}
	else
	{
		if (!buffer.loadFromFile("Filename"))
			cout << "error loading sound" << endl;
		else
			gameSound.setBuffer(buffer);
	}
}


void Sound::play()
{
	gameMusic.stop();
	gameSound.stop();
	if (music)
		gameMusic.play();
	else
		gameSound.play();
}


void Sound::pause()
{

}


Sound::~Sound()
{
}
