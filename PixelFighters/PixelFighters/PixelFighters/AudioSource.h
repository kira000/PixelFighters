#pragma once
#include <SDL_mixer.h>
class AudioSource
{
public:
	AudioSource();
	~AudioSource();
	void Initialize(char* path);
	void Play();
	void Stop();


private:
	Mix_Music *musik;
};

