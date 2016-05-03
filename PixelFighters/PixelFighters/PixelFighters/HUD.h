#pragma once
#include <SDL.h>
class HUD
{
public:
	HUD(SDL_Renderer* _renderer = nullptr,int ScreenWidth = 0,int ScreenHeight = 0 );
	~HUD();
	int Update( int damageP1, int energyP1, int attackLvl, int attackHight);
	void setNumbers(int playNr = 0, int charNr = 0);
	void Render();

private:
	void loadHUD();
	void loadLiveBar(int charNr);
	void loadEndergyBar();
	void loadAttackField();
	
	void setPosition();

	void calcLifeBar(int life);
	void calcEnergyBar(int energy);

	int playerNr;
	
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Texture* text;

	SDL_Rect healthBorder;
	SDL_Rect healthBar;

	SDL_Rect *EnergyBar;
	SDL_Rect *energyLevel;
	SDL_Rect attackField;

	SDL_Rect attackName;

	SDL_Rect healthBorderPos;
	SDL_Rect healthBarPos;
	SDL_Rect energyBarPos;
	SDL_Rect energyLevelPos;
	SDL_Rect attackFieldPos;
	SDL_Rect attackNamePos;
	
	SDL_RendererFlip flip;

	char* hudPath = "Images/GUI/Spritesheetgui.bmp";
	char* attackPath = "Images/GUI/Schrift.bmp";


	int energyBarHeight = 50;
	int energyBarWidth = 80;

	int healthBorderWidth = 80;
	int healthBorderHeight = 16;

	int healthBarWidth = 62;
	int healthBarHeight = 11;

	int energyLevelHeight = 67;
	int energyLevelWidth = 21;

	int attackFieldWidth = 78;
	int attackFieldHeight = 21;

	int attackNameWidth = 80;
	int attackNameHeight = 20;

	float screenWidth1Perc;
	float screenHeight1Perc;

	const int costLow = 20;
	const int costMiddle = 50;
	const int costHight = 70;
	const int costUltimate = 100;

	int energieNr = 0;
	int energieLvl = 0;

};

