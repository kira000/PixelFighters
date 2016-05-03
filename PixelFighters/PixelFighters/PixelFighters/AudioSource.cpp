#include "AudioSource.h"
#include <iostream>


AudioSource::AudioSource()
{
}


AudioSource::~AudioSource()
{
	Mix_HaltMusic();
	Mix_FreeMusic(musik);
}

void AudioSource::Initialize(char* path)
{
	musik =  Mix_LoadMUS(path);
	if (musik == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void AudioSource::Play()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(musik, -1);
	}
	else if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

void AudioSource::Stop()
{
	if (Mix_PausedMusic()==0)
	{
		Mix_PauseMusic();
	}
}