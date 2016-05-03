#include "MainMenu.h"


MainMenu::MainMenu(SDL_Renderer *renderer, Controller p1) : MenuScene(renderer, p1)
{
	loadBackground("Images/Backgrounds/main.bmp");

	maxPos = 3;
	upDown = true;
	moved = true;
	anouncer.Initialize("Audio/Effects/Ansager/PixelFighters.wav");
	anouncer.Play(false);
}


MainMenu::~MainMenu()
{
}

int MainMenu::Update()
{
	
	int res = MenuScene::Update();

	setCursor();

	if (res == 1)
	{
		//backgroundMusik.Stop();
		switch (cursorPosition)
		{
		case 0: return 2; //Debugwert
		case 1: return 5;
		case 2: return 4;
		default:
			break;
		}
	}
		
	return 1;
}

void MainMenu::setCursor()
{
	if (cursorPosition!= 2)
	{
		cursorPos[0].x = SCREEN_WIDTH / 100 * 38;
		cursorPos[1].x = SCREEN_WIDTH / 100 * 55.8;
	}
	else
	{
		cursorPos[0].x = SCREEN_WIDTH / 100 * 36.9;
		cursorPos[1].x = SCREEN_WIDTH / 100 * 57.6;
	}

	switch (cursorPosition)
	{
	case 0: cursorPos[0].y = SCREEN_HEIGHT / 100 * 28.5; cursorPos[1].y = SCREEN_HEIGHT / 100 * 34.7; break;
	case 1: cursorPos[0].y = SCREEN_HEIGHT / 100 * 37.5; cursorPos[1].y = SCREEN_HEIGHT / 100 * 43.7; break;
	case 2: cursorPos[0].y = SCREEN_HEIGHT / 100 * 72.4; cursorPos[1].y = SCREEN_HEIGHT / 100 * 84.2; break;
	default:
		break;
	}
}
