#pragma once
#include "MenuScene.h"
#include "macros.h"


class CharacterSelection  : public MenuScene
{
public:
	CharacterSelection(SDL_Renderer *renderer, Controller p1, Controller p2);
	~CharacterSelection();
	int Update(ChosenFighters &selection);
	int Update(){ return 0; }
	void Render(ChosenFighters &fighters);
	void RenderChoise(ChosenFighters &fighters);

private:
	Controller _p2;
	void setCursor();

	SDL_Rect choise[2];
	SDL_Texture *choiseText[2];
	SDL_Rect RenderPos[2];
	int scale = 3;

	void loadChosenFighter(Fighters chosen,int choiseNr);

	AudioClip fighterChosen;

};

