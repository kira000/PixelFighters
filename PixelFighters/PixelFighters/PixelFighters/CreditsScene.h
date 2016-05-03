#pragma once
#include "MenuScene.h"
class CreditsScene :
	public MenuScene
{
public:
	CreditsScene(SDL_Renderer *renderer, Controller p1);
	~CreditsScene();
	int Update();
private:
	float deltaTime;
	int curBackground=0;

};

