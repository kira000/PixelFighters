#include "SpAttackUltimate.h"


SpAttackUltimate::SpAttackUltimate(SDL_Renderer* renderer, int screenWidth, int screenHeight, char* ultPath, int _width, int _height) : SpecialAttack(renderer, screenWidth, screenHeight)
{

	spAttack.damage = 60;
	width = _width;
	height = _height;
	if (ultPath != nullptr)
	{
		loadImages(ultPath);
	}


}


SpAttackUltimate::~SpAttackUltimate()
{

}


void SpAttackUltimate::loadImages(char* path)
{
	attack.rect = ImageControl::LoadAnimation(path, 0, width, height, 8, &attack.texture, _renderer);
	if (path != "Images/Attacks/Specials/WarriorFinisher.bmp")
	{
		 nrFrames = 4;
	}
	else 
	{
		nrFrames = 5;
	}
	

}

SpAttack SpAttackUltimate::Update(float dt, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms)
{
	frameChange += dt;

	//spAttack.damage = 0;
	spAttack.hits = nullptr;
	spAttack.nrHits = 0;

	move();

	if ((currentFrame == nrFrames - 1 || currentFrame == 3) && !hit)
	{
		spAttack = SpecialAttack::Update(dt, enemy, mobs, platforms, nrMobs, nrPlatforms);
		if (spAttack.nrHits != 0)
		{
			for (int i = 0; i < spAttack.nrHits; i++)
			{
				if (spAttack.hits[i].x == enemy->x && spAttack.hits[i].y == enemy->y)
				{
					hit = true;
				}
			}
			/*if (xVel == 0 && yVel == 0)
			{
				active = false;
			}*/

		}
	}
	else if (yVel != 0 && currentFrame == nrFrames - 1)
	{
		spAttack = SpecialAttack::Update(dt, enemy, mobs, platforms, nrMobs, nrPlatforms);
	}


	if (frameChange >= frameChangeTimer && currentFrame < 3)
	{
		SpecialAttack::switchSprite();
		frameChange = 0;
	}

	return spAttack;
}



void SpAttackUltimate::CreateAttack(SDL_Rect startPos, int type, SDL_RendererFlip _flip)
{
	flip = _flip;
	hit = false;
	switch (type)
	{
	case 0:
		currentPos = startPos;
		currentPos.x -= width / 2;
		currentPos.w *= 3;
		currentPos.h *= 3;
		currentPos.y = -10;
		currentFrame = 0;
		break;
	case 1:
		currentPos = startPos;

		if (_flip == SDL_FLIP_NONE)
		{
			currentPos.x += startPos.w / 2;
			currentPos.w = _screenWidth - currentPos.x;
		}
		else
		{
			currentPos.x = 0;
			currentPos.w = startPos.x;
		}
		currentPos.h *= 3;
		currentPos.y = startPos.y - currentPos.h *0.2;
		currentFrame = 0;

		break;
	case 2:
		currentPos = startPos;
		if (_flip == SDL_FLIP_NONE)
		{
			currentPos.x += startPos.w / 2;
		}
		else
		{
			currentPos.x -= startPos.w ;
		}
		currentPos.w *= 2;
		//currentPos.h *= 3;
		currentPos.y = startPos.y - currentPos.h *0.2;
		currentPos.h *= 2;
		currentFrame = 0;

		break;
	default:
		break;
	}


	switch (type)
	{
	case 0: yVel = 3; xVel = 0; break;
	case 1: break;
	case 2: yVel = 0; if (flip == SDL_FLIP_NONE)
					 {
						xVel = 3;
					 }
					else{
						xVel = -3;
					}
					break;
	default:
		break;
	}

	active = true;

}

void SpAttackUltimate::move()
{
	currentPos.x += xVel;
	currentPos.y += yVel;
}


