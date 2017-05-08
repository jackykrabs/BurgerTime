#pragma once
#include "Sound.h"
class AudioCenter
{
public:
	AudioCenter();
	~AudioCenter();
	bool areSoundsPlaying();
	void playMainTheme();
	void playDeathSound();
	void playRoundStart();
	void playRoundClear();
//private:
	Sound* mainTheme;
	Sound* roundStart;
	Sound* deathSound;
	Sound* roundClear;
	void stopAllSounds();
};

