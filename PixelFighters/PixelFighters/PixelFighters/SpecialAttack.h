#pragma once
#include "ImageControl.h"
#include <iostream>
#include "macros.h"
#include "AudioClip.h"



enum class spAttacks {FalconPwn, GankingLama, PimpSlap, YourMom, 
	Over, Allmighty, DeathTrap, Chaos,
	TrampStamp, ScrewYou, DubStep, Piano,//LineAttacks
	Ultname/*Debugvalue*/};

//Struktur für Spezialattacke nach ausen
typedef struct _spAttackStruct
{
	SDL_Rect* hits = new SDL_Rect();
	int nrHits;
	int damage;

	~_spAttackStruct(){ /*SAFE_DELETE(hits);*/ }
} SpAttack;


//Attacke intern
typedef struct _attack
{
	spAttacks name;
	SDL_Rect* rect;
	SDL_Texture* texture;
	int damage;

	~_attack(){ /*SAFE_DELETE(rect);*/ }
} Attack;


class SpecialAttack
{
public:
	//ctor
	SpecialAttack(SDL_Renderer* renderer = nullptr, int screenWidth = 0, int screenHeight = 0);
	//dtor
	~SpecialAttack();

	//Attacke updaten
	virtual SpAttack Update(float dt,SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms);
	//Attacke kreieren
	virtual void CreateAttack(SDL_RendererFlip flip, SDL_Rect startPos);
	virtual void Render();
	//@return ob Attacke aktiv ist
	bool IsActive();

	AudioClip attackSound;
	AudioClip hitSound;
protected:
	//Sprite bewegen
	virtual void move();
	void switchSprite();

	//Kraft der Attacken
	//schwache Attacke

	//aktive Attacke
	Attack attack;

	SDL_Renderer* _renderer;
	SDL_Rect currentPos;
	SDL_RendererFlip flip;

	SpAttack spAttack;

	bool checkCollision(SDL_Rect rect);

	int direction;

	int nrFrames;
	int currentFrame = 0;

	int FrameTime = 200;

	int scale = 1;

	int xVel = 0;
	int yVel = 0;

	bool active = false;

	int _screenWidth;
	int _screenHeight;
	bool playerHit;
};

