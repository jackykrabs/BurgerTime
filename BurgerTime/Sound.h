#pragma once
#include <SFML\Audio.hpp>

using namespace std;

class Sound
{
public:
	Sound();
	Sound(string, bool);
	void play();
	void stop();
	void pause();
	void getSound();
	void setSound(string);
	bool music;
	sf::SoundBuffer buffer;
	sf::Music gameMusic;
	sf::Sound gameSound;
	~Sound();
};

