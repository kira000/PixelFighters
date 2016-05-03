#pragma once
#include "SDL.h"
#include <stdint.h>
#include <iostream>
#include <vector>

using namespace std;
//Static class to manage the rendering of moving Objects(Characters,mobs)
class ImageControl
{
public:
	//load the spritesheet
	static SDL_Rect* LoadAnimation(char* path, int line, int width, int height, int nrSprites, SDL_Texture** texture, SDL_Renderer* renderer);
	static SDL_Rect* LoadAnimation(char* path, float pos, int width, int height, int nrSprites, SDL_Texture** texture, SDL_Renderer* renderer);
	//render differences
	static void Render( SDL_Rect* positon,SDL_Texture*, SDL_Renderer*, SDL_Rect*, double, SDL_RendererFlip);

	//static const int frameDimension = 66; //größe eines Frames(quadratisch in diesem fall)

private:

	static const uint32_t c_r = 0xff;	//hexwert red
	static const uint32_t c_g = 0;		//hexwert green
	static const uint32_t c_b = 0xff;	//hexwert blue

};

