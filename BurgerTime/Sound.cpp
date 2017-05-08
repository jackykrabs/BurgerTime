#include "stdafx.h"
#include "Sound.h"
#include <iostream>
#include <SFML\Audio.hpp>

using namespace std;


Sound::Sound()
{
}

Sound::Sound(string fileName, bool temp)
{
	music = temp;
	if (music)
	{
		if (!gameMusic.openFromFile("sounds\\" + fileName))
			cout << "error opening music" << endl;
		gameMusic.setLoop(true);
	}
	else
	{
		if (!buffer.loadFromFile("sounds\\" + fileName))
			cout << "error loading sound" << endl;
		else
			gameSound.setBuffer(buffer);
		gameSound.setLoop(false);
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

void Sound::stop()
{
	gameMusic.stop();
	gameSound.stop();
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
