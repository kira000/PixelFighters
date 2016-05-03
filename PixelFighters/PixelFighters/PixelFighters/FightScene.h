#pragma once
#include <list>
#include "Scene.h"
#include "Mob.h"
#include "HUD.h"



typedef struct _doubleInt
{
	int damage;
	int energy;

	_doubleInt(int _damage, int _energy){ damage = _damage; energy = _energy; }
	_doubleInt(){ _doubleInt(0, 0);	}
	_doubleInt operator+=(const _doubleInt& right)
	{
		this->damage += right.damage;
		this->energy += right.energy;
		return *this;
	}
	
	
}EnergyValues;

//Class for managing the FightScreen
class FightScene : public Scene
{
public:
	//Const
	FightScene( SDL_Renderer* renderer, Controller p1, Controller p2, ChosenFighters fighters = ChosenFighters());
	//Dest
	~FightScene();
	//Create Platforms at specific positions
	void createPlatforms(Backgrounds background);
	//Update Method
	int Update();
	//RenderMethod
	void Render();
	

private:

	//PlatformConstants
	Coordinates testCoord[6];

	char* platformPath1 = "Images/Platforms/platform1.bmp"; //später dem Hintergrund entsprechend
	/*char* platformPath2 = "Images/Platforms/platform2.bmp";
	char* platformPath3 = "Images/Platforms/platform3.bmp";
	char* platformPath4 = "Images/Platforms/platform4.bmp";
	char* platformPath5 = "Images/Platforms/platform5.bmp";*/

	char* backgroundPath = "Images/Backgrounds/Background.bmp"; //später auswahl bei Kampstart
	
	//Gamepad(Controller) for Player2
	Controller _p2;
	Coordinates coord;

	//Pointer for the platforms
	//SDL_Surface* platform;
	SDL_Texture* platform1 = nullptr;
	/*SDL_Texture* platform2 = nullptr;
	SDL_Texture* platform3 = nullptr;
	SDL_Texture* platform4 = nullptr;
	SDL_Texture* platform5 = nullptr;
*/

	SDL_Rect* platformRects = new SDL_Rect();

	SDL_Rect victory;
	SDL_Rect victoryPos;

	SDL_Texture *victoryText = nullptr;


	//Enum für Stage
	Backgrounds currentBckg;

	//count op platforms
	int nrPlatforms;

	//Pointer for the mobs
	//Mob* mobs;
	//count of current Mobs
	int nrMobs;
	bool victoryPlayed = false;

	Character char1, char2;


	list<Mob*> mobs;

	float deltaTime = 0;

	float mobSpawnTime = 10;

	float winDelta = 0;

	//Draws the Platforms on the screen
	void drawPlatforms();
	//Draws 1 Platform at a specific coordinate
	void drawPlatform(SDL_Rect);
	//Gets the Images for the stage
	void loadImages();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

	//Load Platform coordinates
	void setPlatformCoordinates();

	EnergyValues updateDamage(StAttack attack, Character* attacking, Character* hit);
	EnergyValues updateDamage(SpAttack attack, Character* attacking, Character* hit);



	//create new Mob

	void createMob();

	void destroyMob(Mob* mob);
	
};

