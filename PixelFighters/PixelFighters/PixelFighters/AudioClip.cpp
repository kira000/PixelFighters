#include "AudioClip.h"
#include <iostream>

AudioClip::AudioClip()
{
}


AudioClip::~AudioClip()
{
	Mix_FreeChunk(soundEffekt);
}


void AudioClip::Initialize(char* path)
{
	soundEffekt = Mix_LoadWAV(path);
	if (soundEffekt == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}

void AudioClip::Play(bool looping)
{
	if (soundEffekt != nullptr)
	{
		if (looping)
		{
			chanal = Mix_PlayChannel(-1, soundEffekt, -1);
		}
		else
		{
			chanal = Mix_PlayChannel(-1, soundEffekt, 0);
			
		}
	}
}


void AudioClip::Stop()
{
	Mix_HaltChannel(chanal);
}