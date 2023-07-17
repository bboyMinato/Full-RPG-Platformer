#include "..\include\SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024 == -1))
		std::cout << "Audio library could not be initialized!" << Mix_GetError() << std::endl;
}

SoundManager::~SoundManager()
{
	Mix_FreeMusic(_music);
	_music == nullptr;
}

Mix_Music* SoundManager::LoadMusic(std::string ID, std::string filepath)
{
	_music = Mix_LoadMUS(filepath.c_str());

	if (_music == nullptr)
		std::cout << "Failed to load the music!" << Mix_GetError() << std::endl;

	_musicMap[ID] = _music;

	return _music;
}

void SoundManager::PlayMusic(int loops)
{
	if (_music != nullptr)
		Mix_PlayMusic(_music, loops);
}

void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}
