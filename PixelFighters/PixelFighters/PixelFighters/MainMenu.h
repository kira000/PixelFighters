#pragma once
#include "MenuScene.h"
class MainMenu :
	public MenuScene
{
public:
	MainMenu(SDL_Renderer *renderer = nullptr, Controller p1 = Controller());
	~MainMenu();
	int Update();

private:
	float deltaTime = 0;
	void setCursor();

};

