#include "SpAttackLine.h"



SpAttackLine::SpAttackLine(SDL_Renderer* renderer, int screenWidth, int screenHeight) : SpecialAttack(renderer,screenWidth,screenHeight)
{
	//Attacken Random zuweisen

	int randNr = rand() % 4;
	// randNr = 2;
	// noch keine animationen
	switch (randNr)
	{
	case 0: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Attackenline.bmp", 0,40,40, 8, &attack.texture, renderer);
		attack.name = spAttacks::FalconPwn;
		attack.damage = 10;
		nrFrames = 8;//Wert einsetzen
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Line/FalconPun/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Line/FalconPun/Hit.wav");
		//damage festlegen
		break;
	case 1: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Attackenline.bmp", 1, 40, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::GankingLama;
		attack.damage = 10;
		nrFrames = 8; 
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Line/GankingLama/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Line/GankingLama/Hit.wav");
		break;

	case 2: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Attackenline.bmp", 2, 40, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::YourMom;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Line/YourMom/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Line/YourMom/Hit.wav");
		break;
	case 3: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Attackenline.bmp", 3, 40, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::PimpSlap;
		attack.damage = 10;
		nrFrames = 8; 
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Line/Pimpslap/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Line/Pimpslap/Hit.wav");
		break;

	default: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Spritesheetnormbig.bmp", 1, 62, 62, 6, &attack.texture, renderer);
		attack.name = spAttacks::FalconPwn;
		nrFrames = 6;
		attack.damage = 10;
		break;
	}
}


SpAttackLine::~SpAttackLine()
{
	//_renderer = nullptr;
}

void SpAttackLine::move()
{
	//Switch auf Bewegungsrichtng
	switch (direction)
	{
	case -1: currentPos.x -= xVel; flip = SDL_FLIP_HORIZONTAL; break;
	case 1: currentPos.x += xVel; flip = SDL_FLIP_NONE; break;
	default:
		break;
	}

	//currentPos.y -= yVel;
	//bewegung  entlang der y-Achse
}


SpAttack SpAttackLine::Update(float dt,SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms)
{
	
	move();
	spAttack = SpecialAttack::Update(dt,enemy, mobs, platforms, nrMobs, nrPlatforms);
	deltaTime += dt;
	if (deltaTime > FrameTime)
	{
		SpecialAttack::switchSprite();
		deltaTime = 0;
	}
	//Schaden der Attacke erhalten
	spAttack.damage =attack.damage;

	//Rendern
	
	//Angriffswerte zurückgeben

	return spAttack;
}