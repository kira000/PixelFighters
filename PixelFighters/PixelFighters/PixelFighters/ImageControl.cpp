#include "ImageControl.h"
#include "macros.h"

//loads the spritesheet and returns the rect
SDL_Rect* ImageControl::LoadAnimation(char* path, int line, int width, int height,int nrSprites, SDL_Texture** texture, SDL_Renderer* renderer)
{
	//get line with animation
	int spriteLine = line * height;
	//create SDL_Rect for clips
	SDL_Rect *spriteClips = new SDL_Rect[nrSprites];

	//load Spritesheet bmp
	if (*texture == nullptr)
	{
		SDL_Surface* loadedSurface = SDL_LoadBMP(path);
		if (loadedSurface == NULL)
		{
			printf("Failed to load char: %s", SDL_GetError());
		}
		//Set colorkey for transparence
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, c_r, c_g, c_b));
		//create Texture from surface
		*texture = SDL_CreateTextureFromSurface(renderer, loadedSurface); 
	}
	//For the nr of clips in animation
	for (int i = 0; i < nrSprites; i++)
	{
		spriteClips[i].x = i * width;	//set Startpoint horizontal
		spriteClips[i].y = spriteLine;	//set Startpoint vertical
		spriteClips[i].w = width;		//set width
		spriteClips[i].h = height;		//set height
	}
	
	//retrun SDL_Rects
	return spriteClips;
}

SDL_Rect* ImageControl::LoadAnimation(char* path, float pos, int width, int height, int nrSprites, SDL_Texture** texture, SDL_Renderer* renderer)
{
	//get line with animation
	int spriteLine = pos;
	//create SDL_Rect for clips

	SDL_Rect* spriteClips = new SDL_Rect[nrSprites];

	//load Spritesheet bmp
	if (*texture == nullptr)
	{
		SDL_Surface* loadedSurface = SDL_LoadBMP(path);
		if (loadedSurface == NULL)
		{
			printf("Failed to load bmp: %s", SDL_GetError());
		}
		//Set colorkey for transparence
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, c_r, c_g, c_b));
		//create Texture from surface
		*texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
		loadedSurface = nullptr;
	}
	//For the nr of clips in animation
	for (int i = 0; i < nrSprites; i++)
	{
		spriteClips[i].x = i * width;	//set Startpoint horizontal
		spriteClips[i].y = spriteLine;			//set Startpoint vertical
		spriteClips[i].w = width;		//set width
		spriteClips[i].h = height;		//set height
	}


	//retrun SDL_Rects
	return spriteClips;
}

//render objects new
void ImageControl::Render(SDL_Rect* position,SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* spriteClip,double angle, SDL_RendererFlip flip)
{
	/*position->w *= scale;
	position->h *= scale;*/
	

	//Copy Texture to destination inclusive rotation and flipping 
	SDL_RenderCopyEx(renderer, texture, spriteClip, position,angle,NULL,flip);
	
}
