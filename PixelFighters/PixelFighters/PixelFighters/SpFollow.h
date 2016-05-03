#pragma once

#include "SpecialAttack.h"

class SpFollow : 
	public SpecialAttack
{
public:
	//ctor
	SpFollow(SDL_Renderer* renderer = nullptr, int screenWidth = 0, int screenHeight = 0);
	//dtor
	~SpFollow();
	//Update SpecialAttack
	virtual SpAttack Update(float dt, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms);

private:

	//time delay
	float deltaTime;
};

