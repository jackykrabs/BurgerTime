#include "stdafx.h"
#include "AudioCenter.h"


AudioCenter::AudioCenter()
{
	mainTheme = new Sound("Main_Theme.wav", true);
	roundClear = new Sound("Round_Clear.wav", false);
	deathSound = new Sound("Death_Sound.wav", false);
	roundStart = new Sound("Round_Start.wav", false);
}


AudioCenter::~AudioCenter()
{
}

bool AudioCenter::areSoundsPlaying()
{
	if (roundStart->gameSound.getStatus() == 2)
		return true;
	if (deathSound->gameSound.getStatus() == 2)
		return true;
	if (roundClear->gameSound.getStatus() == 2)
		return true;
	return false;
}
void AudioCenter::stopAllSounds()
{
	while (roundStart->gameSound.getStatus() != 0){}
	while (deathSound->gameSound.getStatus() != 0){}
	while (roundClear->gameSound.getStatus() != 0){}
	mainTheme->stop();
}

void AudioCenter::playMainTheme()
{
	if (!areSoundsPlaying())
		mainTheme->play();
}

void AudioCenter::playDeathSound()
{
	stopAllSounds();
	deathSound->play();
}

void AudioCenter::playRoundClear()
{
	stopAllSounds();
	roundClear->play();
}

void AudioCenter::playRoundStart()
{
	stopAllSounds();
	roundStart->play();
}