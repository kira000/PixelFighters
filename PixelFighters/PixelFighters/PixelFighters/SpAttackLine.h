#pragma once
#include "SpecialAttack.h"
class SpAttackLine :
	public SpecialAttack
{
public:
	//ctor
	SpAttackLine(SDL_Renderer* renderer = nullptr,int screenWidth = 0, int screenHeight = 0);
	//dtor
	~SpAttackLine();
	//Update SpecialAttack
	virtual SpAttack Update(float dt,SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms);

	

private:
	//move sprites
	void move();

	//time delay
	float deltaTime;
};

