#include "ImageControl.h"
#include "Mob.h"


Mob::Mob(SDL_Renderer* renderer, int _SCREEN_WIDTH, int _SCREEN_HEIGHT)
{
	_renderer = renderer;
	SCREEN_WIDTH = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;
	sprites = nullptr;
	texture = nullptr;
	loadImages();
	deathSound.Initialize("Audio/Effects/MobSounds/Spit_Splat-Mike_Koenig-1170500447.wav");
}


Mob::Mob()
{
	_renderer = nullptr;
	SCREEN_WIDTH = 0;
	SCREEN_HEIGHT = 0;
	sprites = nullptr;
	texture = nullptr;
	loadImages();

}

Mob::~Mob()
{
	SAFE_DELETE(sprites);
	SDL_DestroyTexture(texture);
	spritePath = nullptr;
	_renderer = nullptr;
}



bool Mob::Update(SDL_Rect* platforms, int nrPlatforms, float dt)
{
	timeDelay += dt;
	if (life > 0)
	{
		Move();
		collisionDetection(platforms, nrPlatforms);
	}
	else if (life <= 0)
	{

		return Death();

	}
	//Render();

	ImageControl::Render(&position, texture, _renderer, &currentSprite, 0, flip);

	return false;
}

//void Mob::Render()
//{
//
//}

int Mob::takeDamage(int value)
{
	life -= value;
	if (life <= 0)
	{
		currentSprite = sprites[2];
		return energy;
	}
	/*
	if (life <= halfLife)
	{
		currentSprite = sprites[1];
	}
	else if (life <= lowLife)
	{
	currentFrameIndex = 2;
	}*/
	return 0;
}

void Mob::loadImages()
{
	sprites = ImageControl::LoadAnimation(spritePath, 0, mobWidth, mobHeight, 1, &texture, _renderer);
	position.w = mobWidth * 2;
	position.h = mobHeight * 2;
	currentSprite = sprites[0];
}

void Mob::Move()
{

	if (!jumping && !airborne)
	{
		if (timeDelay > 2000)
		{
			randNr = rand() % 3 + 1;
			timeDelay = 0;
		}
	}
	else
	{
		if (timeDelay > 2000)
		{
			randNr = rand() % 2 + 1;
			timeDelay = 0;
		}

	}

	switch (randNr)
	{
	case 1: position.x -= walkSpeed; flip = SDL_FLIP_HORIZONTAL; break;
	case 2: position.x += walkSpeed; flip = SDL_FLIP_NONE; break;
	case 3: jumping = true;
	default:
		break;
	}

	if (jumping && !airborne)
	{
		jumpTimer++;
		if (jumpTimer < jumpHeight){
			position.y -= jumpSpeed;
		}
		else
		{
			jumping = false;
			airborne = true;
			jumpTimer = 0;
		}

	}
	else
	{
		addGravity();
	}
	if (position.x < 0)
	{
		position.x += walkSpeed;
	}
	if (position.x > SCREEN_WIDTH - position.w)
	{
		position.x -= walkSpeed;
	}

}

//returns true if animation is finished
bool Mob::Death()
{
	if (timeDelay > 20000)
	{
		deathSound.Play(false);
		return true;
	}
	//bool if mob is dead
	return false;
}

void Mob::addGravity()
{
	position.y += 1;
}

void Mob::collisionDetection(SDL_Rect* RectArray, int rectCount)
{
	for (int i = 0; i < rectCount; i++)
	{
		if (checkCollision(RectArray[i]))
		{
			if (position.y + position.h <= RectArray[i].y + 2)
			{
				position.y -= gravity;
				airborne = false;
			}
		//	else
		//	{
		//		airborne = true;
		//	}
		//}
		//else
		//{
		//	airborne = true;
		}
	}
}

bool Mob::checkCollision(SDL_Rect rect)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = position.x;
	rightA = position.x + position.w;
	topA = position.y;
	bottomA = position.y + position.h;

	//Calculate the sides of rect B
	leftB = rect.x;
	rightB = rect.x + rect.w;
	topB = rect.y;
	bottomB = rect.y + rect.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}


