#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_rect.h>
//#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;
	SDL_Surface* background = NULL;

	SDL_Surface* stand_left_right = NULL;

	SDL_Rect rect;
	SDL_Rect character_origin;

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, background);
	SDL_Texture* texture_standleft = SDL_CreateTextureFromSurface(renderer, stand_left_right);
	SDL_Texture* texutre_standright = SDL_CreateTextureFromSurface(renderer, stand_left_right);
	


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN && SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			cout << "Debug => Resolution: " << SCREEN_HEIGHT << "x" << SCREEN_WIDTH << endl;
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface(window);
			Sleep(500);
		}
	}
	// background sprite
	background = SDL_LoadBMP("background1.bmp");

	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(background, NULL, screenSurface, &rect);
	// ////

	//character init.
	character_origin.x = 100;
	character_origin.y = 450;
	character_origin.w = 128;
	character_origin.h = 256;
	// //////


	//stand left init.
	bool left = false;
	stand_left_right = SDL_LoadBMP("stand_left.bmp");
	SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
	// //////////

	// stand right init.
	bool right = true;
	stand_left_right = SDL_LoadBMP("stand_right.bmp");
	SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
	// ///////////

	bool quit = false;
	SDL_UpdateWindowSurface(window);
	SDL_Event e;
	while (!quit)
	{

		if (GetAsyncKeyState(VK_LEFT))
		{
			right = false;
			left = true;
			stand_left_right = SDL_LoadBMP("stand_left.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x -= 20;
			SDL_UpdateWindowSurface(window);
			Sleep(15);
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			left = false;
			right = true;
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 20;
			SDL_UpdateWindowSurface(window);
			Sleep(15);
		}

		if (GetAsyncKeyState(VK_UP))
		{
#pragma region left
			if (left == true)
			{
				// up
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				// down
				Sleep(40);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
			}
#pragma endregion

#pragma region right
			if (right == true)
			{
				//up
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y -= 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(40);
				//down
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(10);
				character_origin.y += 25;
				SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
				SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
				SDL_UpdateWindowSurface(window);
				Sleep(30);
			}
#pragma endregion
		}


		if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_UP))
		{
			//up => right		frame 1
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			// frame2
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			// frame 3
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			// frame 4
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 5
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 6
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 7
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 8
			character_origin.y -= 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			Sleep(10);
			// right => down		frame 1
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			// frame 2
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 3
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 4
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			Sleep(5);
			// frame 5
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 6
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			//frame 7
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
			// frame 8
			character_origin.y += 30;
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			SDL_UpdateWindowSurface(window);
			stand_left_right = SDL_LoadBMP("stand_right.bmp");
			SDL_BlitScaled(background, NULL, screenSurface, &rect); //background reload
			SDL_BlitScaled(stand_left_right, NULL, screenSurface, &character_origin);
			character_origin.x += 10;
			SDL_UpdateWindowSurface(window);
		}


		if (GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		{
			Sleep(100);
			printf("Escape: Quit");
			quit = true;
		}



		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		SDL_UpdateWindowSurface(window);
	}
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

void UpdateBackground()
{

	Sleep(1000);

}
