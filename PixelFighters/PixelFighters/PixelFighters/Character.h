#include <Windows.h>
#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_rect.h>
#include <iostream>
#include "SpecialAttack.h"
#include "SpAttackLine.h"
#include "Controller.h"
#include "HUD.h"
#include "macros.h"
#include "SpAttackUltimate.h"
#include "SpRound.h"
#include "SpFollow.h"

enum class Fighters{ Warrior, Master, Thing, No }; //Names are Subject to change

enum class StandartAttack{ Punch, Kick, Special };

typedef struct _AttackStruct
{
	SDL_Rect* hits = new SDL_Rect();
	StandartAttack attackType;
	int nrHits;
	int damage;

	~_AttackStruct(){ /*SAFE_DELETE(hits);*/ }
}StAttack;

typedef struct _characters
{
	Fighters fighter1;
	Fighters fighter2;
	_characters(Fighters f1, Fighters f2 ){ fighter1 = f1; fighter2 = f2; }
	_characters(){};

}ChosenFighters;

class Character
{

public:
	//const
	Character(SDL_Renderer* renderer, int screenWidth, int screenHeight);
	//std const
	Character();
	//dest
	~Character();

	//Methode zum Updaten des Characters
	//@return struct:Art der Attacke,Anzahl der Treffer,getroffene Gegenstände, Schaden
	StAttack Update(float dt, Button pressed, XINPUT_AXIS axis, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* Platforms, int mobCount, int platformCount);



	//Methode zum Updaten einer Spezialattacke
	//@return struct:Anzahl der Treffer,getroffene Gegenstände, Schaden
	SpAttack UpdateSpecial(SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* Platforms, int mobCount, int platformCount);

	

	//Methode zum Updaten des erhaltenen Schadens
	//@param erhaltener Schaden, erhaltene Energie
	void UpdateDamage(int damage, int energy);

	//aktuelle Position des Characters
	SDL_Rect currentPos;

	void createFighters(Fighters fighter, int playerNr);

	void RenderSpecial();

	void RenderGUI();

	//Breite des Fensters
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	//Höhe des Fensters
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	bool isBlocking() { return blocking; }

	bool IsUlt(){ return isUlt; }



	//Höhe des Leben
	int live = 100;
	//Höhe der Energie
	int energy = 50;

	int hitcount = 0;
private:

	bool roundFollow = false;

	int ultType = 0;
	//Lädt Sprites aus Datei
	void LoadSprites(char* charpath);

	//Horizontale Bewegung
	//@param ausgelesene Werte der AnalogenKomponente´n
	void Walk(XINPUT_AXIS axis);

	//Vertikale Bewegung nach oben
	void Jump();
	//Abspielen Schlaganimation
	void Punch(SDL_Rect* mobs, SDL_Rect* enemy, int mobCount);

	//Abspielen Tretanimation
	void Kick(SDL_Rect* mobs, SDL_Rect* enemy, int mobCount);

	bool Block(bool blocking);

	//Neuberechnung der Leben
	void CalcLife(int damage);

	void Vanish();

	void Appear();

	//Neuberechnung der Energie
	void CalcEnergy(int Energy);

	//Kollisionsabfrage eines Arrays
	//@return getroffene Objekte
	SDL_Rect* collisionDetection(SDL_Rect* RectArray, int rectCount, bool isPlatform);

	//Kollisionsabfrage eines einzelnen Objekts
	bool Character::checkCollision(SDL_Rect rect);

	//Einberechnung der Gravitation
	void AddGravity();

	//Struct für normale Attack
	StAttack attack;

	//Struct für Spezialattacke
	SpAttack spattack;

	//Ausrichtung des Sprites
	SDL_RendererFlip flip;

	//Pointer: Texture des Characters
	SDL_Texture* texture;

	//Animation Rects als Array

	//IdleFrame
	SDL_Rect _Idle;

	//Ganganimation
	SDL_Rect* _Walk;

	//Schlaganimation
	SDL_Rect* _Punch;
	//Trittanimation
	SDL_Rect* _Kick;

	SDL_Rect* _Block;

	SDL_Rect* _Jump;
	SDL_Rect* _Damage;

	SDL_Rect* _Vanish;
	SDL_Rect* _Appear;

	SDL_Rect* ahits;

	//Renderer
	SDL_Renderer* _renderer;

	//Aktuelles Rekt zum Spriteauslesen 
	SDL_Rect current;

	HUD _hud;

	int _playerNr;

	int charWidth;
	int charHeight;

	//Movement values

	//Wert Gravitation
	const int gravity = 5;

	//Laufgeschwindigkeit
	const int walkSpeed = 3;

	//Sprunggeschwindigkeit
	const int jumpSpeed = 5;

	//Sprunghöghe
	const int jumpHeight = 700;
	//Zeit zwischen Laufsprites
	const int timeWalkFrame = 100;
	//Zeit zwischen Trittsprites
	const int kickTimer = 70;
	//Zeit zwischen Schlagsprites
	const int punchTimer = 50;
	//Zeit zum anzeigen der Animation
	const int blockAnimationTimer = 70;

	const int jumpAnimationTimer = 50;

	//Maximale Zeit in der nach Aufpauern Spezialattacke aktiviert werden kann
	const float maxSpTime = 200000000.0f;
	const float spLvlRaisedTime = 400;
	const float scale = 1.5;


	//Energy constants

	const int costLow = 20;
	const int costMiddle = 50;
	const int costHigh = 70;
	const int costUltimate = 100;

	const int maxEnergy = 100;

	//Timers

	float spTimer = maxSpTime;
	float jumpDuration = 0;
	float walkFrameChange = 0;
	float kickFrameChange = 0;
	float punchFrameChange = 0;
	float blockFrameChange = 0;
	float jumpFrameChange = 0;
	float damageTiming = 0;


	float vanishFrameChange = 0;

	bool blockFinished;
	bool playerFreeze = false;

	//SpecialAttacks
	//Path for the SpecialAttack-Sprites
	char* ultpath = nullptr;

	int attackHeight = 0;

	//Pointer to SpecialAttack-class
	SpecialAttack *spAttck;

	SpAttackLine *spAttackLine;
	//Number for the current AttackLevel (small/middle/ultimate)
	SpRound* spRound;
	SpFollow* spFollow;
	SpAttackUltimate *spUlt;


	AudioClip jumpSound;
	AudioClip punchSound;
	AudioClip kickSound;
	AudioClip UltAttackSound;
	

	int attackLevel = 0;
	int ultCount;

	//aktueller sprite in entsprechenden Array
	int spriteNr = 0;

	//Bools auf Bewegungsmuster

	bool kick = false;
	bool punch = false;
	bool jumping = false;
	bool airborne = false;
	bool move = false;
	bool lvlRaised = false;
	bool blocking = false;

	bool isVanishing = false;
	bool isAppearing = false;

	bool isUlt;

	float dt;
};
