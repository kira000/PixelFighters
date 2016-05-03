#include "SpRound.h"



SpRound::SpRound(SDL_Renderer* renderer, int screenWidth, int screenHeight) : SpecialAttack(renderer, screenWidth, screenHeight)
{
	//Attacken Random zuweisen

	int randNr = rand() % 4;
	// randNr = 2;
	// noch keine animationen
	switch (randNr)
	{
	case 0: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Round/SpriteSheetRound.bmp", 0, 110, 90, 8, &attack.texture, renderer); // 6 +2 space
		attack.name = spAttacks::Over;
		attack.damage = 10;
		nrFrames = 8;//Wert einsetzen
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Over/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Over/Hit.wav");
		//damage festlegen
		break;
	case 1: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Round/SpriteSheetRound.bmp", 1, 110, 90, 8, &attack.texture, renderer);
		attack.name = spAttacks::Allmighty;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Allmighty/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Allmighty/Hit.wav");
		break;

	case 2: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Round/SpriteSheetRound.bmp", 2, 110, 90, 8, &attack.texture, renderer);
		attack.name = spAttacks::DeathTrap;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Deahtrap/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Deahtrap/Hit.wav");
		break;
	case 3: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Round/SpriteSheetRound.bmp", 3, 110, 90, 8, &attack.texture, renderer);
		attack.name = spAttacks::Chaos;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Over/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Round/Over/Hit.wav");
		break;

	default: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Spritesheetnormbig.bmp", 1, 62, 62, 6, &attack.texture, renderer);
		attack.name = spAttacks::FalconPwn;
		nrFrames = 6;
		attack.damage = 10;
		break;
	}

	scale = 2;
}


SpAttack SpRound::Update(float dt, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms)
{
	//move();
	spAttack.hits = nullptr;
	spAttack.nrHits = 0;
	spAttack = SpecialAttack::Update(dt, enemy, mobs, platforms, nrMobs, nrPlatforms);
	deltaTime += dt;
	if (deltaTime > FrameTime)
	{
		SpecialAttack::switchSprite();
		deltaTime = 0;
	}
	if (currentFrame >= 7)
	{
		
		active = false;
	}
	//Schaden der Attacke erhalten
	spAttack.damage = attack.damage;

	//Rendern

	//Angriffswerte zurückgeben

	return spAttack;
}


SpRound::~SpRound()
{
}
