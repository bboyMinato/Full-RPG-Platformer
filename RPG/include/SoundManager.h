#pragma once
#include <string>
#include <map>
#include "SDL_mixer.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	Mix_Music* LoadMusic(std::string ID, std::string filepath);

	// Number of times to play music
	// 0 means play once and stop
	// -1 means plays infinitely 
	void PlayMusic(int loops);

	void PauseMusic();

	// Set volume of music (range from 0 to 128)
	void SetMusicVolume(int volume);

private:
	Mix_Music* _music = nullptr;

	std::map<std::string, Mix_Music*> _musicMap;
};

