#pragma once
#include <SFML\Audio.hpp>

using namespace std;

class Sound
{
public:
	Sound();
	Sound(string, bool);
	void play();
	void getSound();
	void pause();
	void setSound(string);
	bool music;
	sf::SoundBuffer buffer;
	sf::Music gameMusic;
	sf::Sound gameSound;
	~Sound();
};

