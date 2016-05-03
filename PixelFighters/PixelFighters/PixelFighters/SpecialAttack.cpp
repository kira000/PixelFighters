#include "SpecialAttack.h"


SpecialAttack::SpecialAttack(SDL_Renderer* renderer , int screenWidth, int screenHeight)
{
	_renderer = renderer;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	playerHit = false;
	
}


SpecialAttack::~SpecialAttack()
{
	_renderer = nullptr;
	playerHit = false;
	
}


SpAttack SpecialAttack::Update(float dt,SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms)
{
	spAttack.hits = new SDL_Rect();
	spAttack.nrHits = 0;
	//Bewegung aufrufen
	//move();

	//Kollisionen überprüfen wenn kollidert registrieren
	if (!playerHit && checkCollision(*enemy))
	{
		//auf ExplosionsSprites wechseln
		spAttack.hits[0] = *enemy;
		spAttack.nrHits++;
		playerHit = true;
		if (xVel != 0 || yVel != 0)
		{
			hitSound.Play(false);
		}
	}

	for (int i = 0; i < nrMobs; i++)
	{
		if (checkCollision(mobs[i]))
		{
			//auf ExplosionsSprites wechseln
			spAttack.hits[spAttack.nrHits] = mobs[i];
			spAttack.nrHits++;
		}
	}

	//for (int i = 0; i < nrPlatforms; i++)
	//{
	//	if (checkCollision(platforms[i]))
	//	{
	//		//auf ExplosionsSprites wechseln
	//		spAttack.hits[spAttack.nrHits] = platforms[i];
	//		spAttack.nrHits++;
	//	}
	//}


	if (currentPos.x - currentPos.w < 0 || currentPos.x > _screenWidth)
	{
		active = false;
	}

	if (currentPos.y > _screenHeight)
	{
		active = false;
	}
	
	return spAttack;
}

void SpecialAttack::Render()
{
	ImageControl::Render(&currentPos, attack.texture, _renderer, &attack.rect[currentFrame], 0, flip);
}


bool SpecialAttack::checkCollision(SDL_Rect rect)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = currentPos.x;
	rightA = currentPos.x + currentPos.w;
	topA = currentPos.y;
	bottomA = currentPos.y + currentPos.h;

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



void SpecialAttack::move()
{
	//Switch auf Bewegungsrichtng
	switch (direction)
	{
	case -1: currentPos.x -= xVel; flip = SDL_FLIP_HORIZONTAL; break;
	case 0: /* bewegung x-Achse = neutral;*/ break; 
	case 1: currentPos.x += xVel; flip = SDL_FLIP_NONE; break;
	default:
		break;
	}

	currentPos.y -= yVel;
	
	//bewegung  entlang der y-Achse

}

void SpecialAttack::CreateAttack( SDL_RendererFlip flip, SDL_Rect startPos)
{
	//Switch auf Attackenlevel
	playerHit = false;
	currentPos = startPos;
	currentPos.x += 10;
	currentFrame = 0;

	currentPos.w *= scale;
	currentPos.h *= scale;

	if (true /*activeAttack.name != spAttacks::[Attacken mit senkrechten bewegungen]*/)
	{
		switch (flip)
		{
		case SDL_FLIP_NONE: direction = 1; break;
		case SDL_FLIP_HORIZONTAL: direction = -1; break;
		default:
			break;
		}
	}
	
	switch (attack.name)
	{
	case spAttacks::FalconPwn: xVel = 3; break;
		//velocitys setzen
	case spAttacks::GankingLama: xVel = 3; break;
	case spAttacks::PimpSlap: xVel = 3; break;
	case spAttacks::YourMom: xVel = 3; break;
	default:
		break;
	}

	active = true;
}


//True wenn eine Attack aktiv ist
bool SpecialAttack::IsActive()
{
	return active;
}

void SpecialAttack::switchSprite()
{
	if (currentFrame < nrFrames -1)
	{
		currentFrame++;
	}
	else if (attack.name == spAttacks::GankingLama)
	{
		currentFrame = 3;
	}
}