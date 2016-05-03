#pragma once
#include <SDL.h>
#include "macros.h"
#include "AudioClip.h"


class Mob
{
public:
	Mob(SDL_Renderer* renderer , int _SCREEN_WIDTH,int _SCREEN_HEIGHT);
	Mob();
	~Mob();

	//@return mob is
	bool Update(SDL_Rect* platforms, int nrPlatforms, float dt);
	//void Render();
	int takeDamage(int);

	int getLife(){ return life; }
	void setLife(int value){ life = value; }

	SDL_Rect position;
private:
	SDL_Rect *sprites = nullptr;

	SDL_Rect currentSprite;
	SDL_Texture *texture = nullptr;
	SDL_Renderer *_renderer = nullptr;

	char* spritePath = "Images/Mobs/Enemy.bmp";

	//Debugwerte
	int life = 5;
	const int energy = 10;
	const int walkSpeed = 1;
	const int jumpSpeed = 1;
	const int jumpHeight = 200;
	const int gravity = 1;

	float jumpTimer = 0;

	
	int timeDelay = 0;

	int randNr = 0;

	bool jumping = false;
	bool airborne = true;


	const int halfLife = 5;
	//const int lowLife = 25;

	const int mobWidth = 30;
	const int mobHeight = 30;


	void Move();
	bool Death();
	void addGravity();

	void loadImages();
	void collisionDetection(SDL_Rect* RectArray, int rectCount);
	bool checkCollision(SDL_Rect rect);

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_RendererFlip flip;

	AudioClip deathSound;
};

