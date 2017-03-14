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
		if (!buffer.loadFromFile(fileName))
			cout << "error loading sound" << endl;
		else
			gameSound.setBuffer(buffer);
	}
}


void Sound::play()
{
	pause();
	if (music)
		gameMusic.play();
	else
		gameSound.play();
}


void Sound::pause()
{
	gameSound.pause();
	gameMusic.pause();
}


void Sound::setSound(string fileName)
{
	if (!music)
	{
		if (!buffer.loadFromFile(fileName))
			cout << "error loading sound" << endl;
		else
			gameSound.setBuffer(buffer);
	}
	else
		cout << "error cannot set for music" << endl;
}

Sound::~Sound()
{
}
