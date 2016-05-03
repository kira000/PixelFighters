#include "SpFollow.h"



SpFollow::SpFollow(SDL_Renderer* renderer, int screenWidth, int screenHeight) : SpecialAttack(renderer, screenWidth, screenHeight)
{
	//Attacken Random zuweisen

	int randNr = rand() % 4;
	// randNr = 2;
	// noch keine animationen
	switch (randNr)
	{
	case 0: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Follow/Spfollow.bmp", 0, 70, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::TrampStamp;
		attack.damage = 10;
		nrFrames = 8;//Wert einsetzen
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/TrampStamp/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/TrampStamp/Hit.wav");
		//damage festlegen
		break;
	case 1: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Follow/Spfollow.bmp", 1, 70, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::ScrewYou;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/SrewYou/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/SrewYou/Hit.wav");
		break;

	case 2: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Follow/Spfollow.bmp", 2, 70, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::DubStep;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/Dupstep/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/Dupstep/Hit.wav");
		break;
	case 3: attack.rect = ImageControl::LoadAnimation("Images/Attacks/Follow/Spfollow.bmp", 3, 70, 40, 8, &attack.texture, renderer);
		attack.name = spAttacks::Piano;
		attack.damage = 10;
		nrFrames = 8;
		attackSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/Pianos/Attack.wav");
		hitSound.Initialize("Audio/Effects/AttackSounds/Special/Follow/Pianos/Hit.wav");
		break;

	default: attack.rect = ImageControl::LoadAnimation("Images/Attacks/LineAttacks/Spritesheetnormbig.bmp", 1, 62, 62, 6, &attack.texture, renderer);
		attack.name = spAttacks::FalconPwn;
		nrFrames = 6;
		attack.damage = 10;
		break;
	}

}


SpFollow::~SpFollow()
{
}


SpAttack SpFollow::Update(float dt, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms)
{

	move();
	spAttack = SpecialAttack::Update(dt, enemy, mobs, platforms, nrMobs, nrPlatforms);
	deltaTime += dt;
	if (deltaTime > FrameTime)
	{
		SpecialAttack::switchSprite();
		deltaTime = 0;


		if (currentFrame >= 7)
		{
			active = false;
		}
	}
	//Schaden der Attacke erhalten
	spAttack.damage = attack.damage;

	//Rendern

	//Angriffswerte zurückgeben

	return spAttack;
}
