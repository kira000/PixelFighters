#include "ImageControl.h"
#include "macros.h"
#include "HUD.h"


HUD::HUD(SDL_Renderer* _renderer, int ScreenWidth, int ScreenHeight ) //0 = thing 1 = master 2 = warrior
{
	renderer = _renderer;
	screenWidth1Perc = ScreenWidth / 100;
	screenHeight1Perc = ScreenHeight / 100;

}


HUD::~HUD()
{
	SDL_DestroyTexture(texture);
	renderer = nullptr;
	hudPath = nullptr;
	SAFE_DELETE(EnergyBar);

}

void HUD::setNumbers(int playNr , int charNr )
{
	playerNr = playNr;
	loadLiveBar(charNr);
	loadEndergyBar();

	loadAttackField();
	setPosition();
}

void HUD::loadHUD()
{

}

void HUD::loadLiveBar(int charNr)
{
	SDL_Rect* rect;
	rect = ImageControl::LoadAnimation(hudPath, (float)energyBarHeight, healthBorderWidth, healthBorderHeight, 3, &texture, renderer);
	healthBorder = rect[charNr];

	healthBar = *ImageControl::LoadAnimation(hudPath, (float)energyBarHeight + healthBorderHeight, healthBarWidth, healthBarHeight, 1, &texture, renderer);

}

void HUD::loadEndergyBar()
{
	EnergyBar = ImageControl::LoadAnimation(hudPath, 0, energyBarWidth, energyBarHeight, 6, &texture, renderer);
	energyLevel = ImageControl::LoadAnimation(hudPath, (float)energyBarHeight + healthBorderHeight + healthBarHeight + attackFieldHeight, energyLevelWidth, energyLevelHeight, 5, &texture, renderer);
}

void HUD::loadAttackField()
{
	attackField = *ImageControl::LoadAnimation(hudPath, (float)energyBarHeight + healthBorderHeight + healthBarHeight, attackFieldWidth, attackFieldHeight, 1, &texture, renderer);

}



int HUD::Update(int live, int energy, int attackLvl, int attackHight)
{
	calcLifeBar(live);
	calcEnergyBar(energy);
	energieLvl = attackLvl;

	if (attackHight != 0)
	{
		printf("hi");
	}
	attackName = *ImageControl::LoadAnimation(attackPath, attackHight, attackNameWidth, attackNameHeight, 1, &text, renderer);
	
	Render();
	return 0;
}
void HUD::Render()
{
	


	SDL_RenderCopyEx(renderer, texture, &healthBar, &healthBarPos, 0, NULL, flip);
	SDL_RenderCopyEx(renderer, texture, &healthBorder, &healthBorderPos, 0, NULL, flip);

	SDL_RenderCopyEx(renderer, texture, &EnergyBar[energieNr], &energyBarPos, 0, NULL, flip);
	SDL_RenderCopyEx(renderer, texture, &energyLevel[energieLvl], &energyLevelPos, 0, NULL, flip);
	SDL_RenderCopyEx(renderer, texture, &attackField, &attackFieldPos, 0, NULL, flip);
	SDL_RenderCopyEx(renderer, text, &attackName, &attackNamePos, 0, NULL, flip);	


}




void HUD::setPosition()
{
	if (playerNr == 0)
	{
		healthBorderPos.x = screenWidth1Perc * 4;

		healthBarPos.x = screenWidth1Perc * 4.4;

		energyBarPos.x = 1;

		energyLevelPos.x = 1;

		attackFieldPos.x = screenWidth1Perc * 30 - attackFieldWidth * 5 / 2;
		attackNamePos.x = screenWidth1Perc * 30 - attackNameWidth;
		flip = SDL_FLIP_NONE;

	}
	else
	{
		healthBorderPos.x = screenWidth1Perc * 75;

		healthBarPos.x = screenWidth1Perc * 80.7;

		energyBarPos.x = screenWidth1Perc * 100 - energyBarWidth*1.6;

		energyLevelPos.x = screenWidth1Perc * 100 - 5;

		attackFieldPos.x = screenWidth1Perc * 70 - attackFieldWidth * 5 / 2;
		attackNamePos.x = screenWidth1Perc * 70 - attackNameWidth;

		flip = SDL_FLIP_HORIZONTAL;
	}

	energyBarPos.y = screenHeight1Perc * 91;

	energyLevelPos.y = screenHeight1Perc * 10;

	healthBorderPos.y = screenHeight1Perc * 4;
	healthBarPos.y = screenHeight1Perc * 5.3;


	healthBorderPos.w = healthBorder.w * 5;
	healthBorderPos.h = healthBorder.h * 5;

	healthBarPos.w = healthBar.w * 5;
	healthBarPos.h = healthBar.h * 5;

	energyBarPos.w = energyBarWidth * 2;
	energyBarPos.h = energyBarHeight * 2;

	energyLevelPos.w = energyLevelWidth * 2;
	energyLevelPos.h = energyLevelHeight * 2;

	
	attackFieldPos.y = screenHeight1Perc * 94;
	attackFieldPos.w = attackFieldWidth * 5;
	attackFieldPos.h = attackFieldHeight * 3.5;

	
	attackNamePos.y = screenHeight1Perc * 96;
	attackNamePos.w = attackNameWidth * 2;
	attackNamePos.h = attackFieldHeight *2;
}

void HUD::calcLifeBar(int life)
{
	healthBar.w = healthBarWidth / 100.0 * life;


	int oldPos = healthBarPos.w;

	healthBarPos.w = healthBarWidth * 5 / 100.0 * life;
	if (playerNr == 1)
	{
		if (oldPos != healthBarPos.w)
		{
			healthBarPos.x += oldPos - healthBarPos.w;
		}
		//healthBarPos.x += healthBarPos.w - healthBarPos.w / 100.0 * life;
	}

}

void HUD::calcEnergyBar(int energy)
{
	if (energy >= costUltimate)
	{
		energieNr = 5;
	}
	else if (energy >= costHight)
	{
		energieNr = 4;
	}
	else if (energy >= costMiddle)
	{
		energieNr = 3;
	}
	else if (energy >= costLow)
	{
		energieNr = 2;
	}
	else
	{
		energieNr = 0;
	}
}

