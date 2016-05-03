#include "targetver.h"
#include "Controller.h"
#include <stdio.h>
#include "Scene.h"
#include "FightScene.h"
#include "MainMenu.h"
#include "CharacterSelection.h"
#include "CreditsScene.h"
#undef main

#include <stdlib.h>
#include <crtdbg.h>
#include <SDL_mixer.h>
#include <time.h>
#define CRTDBG_MAP_ALLOC

enum class Scenes{ MenuScene, CharacterSelectionScreen, FightScene, End, Credits };

#pragma region globals
//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Variables for Scenes

MainMenu *menu = nullptr;
CharacterSelection *select = nullptr;
FightScene *fight = nullptr;
CreditsScene *credits;
//chosen Fighters for fight
ChosenFighters fighters;

int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

#pragma endregion

#pragma region FunctionHeaders
Scenes Fight(Controller p1, Controller p2, ChosenFighters fighters);
Scenes Selection(Controller p1, Controller p2);
Scenes Menu(Controller p1);
Scenes Credits(Controller p1);
Scenes getCurrentScene(int res);

bool windowSetUp();
void close();
#pragma endregion



int main(int argc, char **argv)
{
	srand(time(nullptr));
	fighters.fighter1 = Fighters::No;
	fighters.fighter2 = Fighters::No;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool quit = false;

	Controller p1(0);
	Controller p2(1);

	Scenes scene = Scenes::MenuScene;	//fürs erste


	if (windowSetUp())
	{
		while (!quit)
		{
			switch (scene)
			{
			case Scenes::MenuScene: scene = Menu(p1); break;
			case Scenes::CharacterSelectionScreen: scene = Selection(p1, p2); break;
			case Scenes::FightScene: scene = Fight(p1, p2, fighters); break;	//Rückgabewert von Auswahl benötigt
			case Scenes::End: quit = true; break;
			case Scenes::Credits: scene = Credits(p1); break;
			default: quit = true;
				break;
			}
			//SDL_RenderPresent(gRenderer);
		}
		close();
		return 0;
	}
	return -1;
}


bool windowSetUp(){
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Pixelfighters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//Set Fullscreen
		//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize SDL_mixer 
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
				{ 
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); 
					success = false; 
				}
			}
		}
	}

	return success;
}



Scenes Menu(Controller p1)
{
	SAFE_DELETE(fight);
	SAFE_DELETE(select);
	int res = 0;
	if (menu == nullptr)
	{
		menu = new MainMenu(gRenderer, p1);
	}

	res = menu->Update();
	menu->Render(true);

	return getCurrentScene(res);
}

Scenes Selection(Controller p1, Controller p2)
{
	SAFE_DELETE(menu);
	int res = 0;
	if (select == nullptr)
	{
		fighters.fighter1 = fighters.fighter2 = Fighters::No;
	select = new CharacterSelection(gRenderer,p1, p2);
	}
	res = select->Update(fighters);
	select->Render(fighters);
	
	
	return getCurrentScene(res);
}

Scenes Fight(Controller p1, Controller p2, ChosenFighters fighters){
	//Scenes scene = Scenes::FightScene;
	SAFE_DELETE(select);
	int res = 0;

	if (fight == nullptr)
	{

		Sleep(500);
		//SDL_RenderClear(gRenderer);
		fight = new FightScene(gRenderer, p1, p2, fighters); 
	}
	res = fight->Update();

	return getCurrentScene(res);
}


Scenes Credits(Controller p1)
{
	//Scenes scene = Scenes::FightScene;
	SAFE_DELETE(menu);
	int res = 0;

	if (credits == nullptr)
	{

		
		credits = new CreditsScene(gRenderer, p1 );
	}
	res = credits->Update();
	credits->Render(true);

	return getCurrentScene(res);
}

Scenes getCurrentScene(int res)
{
	switch (res)
	{
	case 1: return Scenes::MenuScene; break;
	case 2: return Scenes::CharacterSelectionScreen; break;
	case 3: return Scenes::FightScene; break;
	case 4: return Scenes::End; break;
	case 5: return Scenes::Credits;
	default: return Scenes::MenuScene; break;
		break;
	}
}


void close()
{
	//SDL_RenderClear(gRenderer);

	Sleep(200);

	SAFE_DELETE(fight);
	SAFE_DELETE(menu);
	SAFE_DELETE(select);

	/*if (gRenderer != nullptr)
	{
		SDL_RenderClear(gRenderer);
		SDL_DestroyRenderer(gRenderer);
		gRenderer = nullptr;
	}*/

	if (gWindow != nullptr)
	{
		SDL_DestroyWindow(gWindow);
		gWindow = nullptr;
	}
	SDL_Quit();
}