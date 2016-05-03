#pragma once
#include <SDL_mixer.h> 

class AudioClip //Class Soundeffekts
{
public:
	AudioClip();
	~AudioClip();
	void Initialize(char* path);
	void Play(bool repeating);
	void Stop();

private:
	Mix_Chunk *soundEffekt;
	int chanal;
};

