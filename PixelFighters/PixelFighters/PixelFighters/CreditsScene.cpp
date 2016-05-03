#include "CreditsScene.h"


CreditsScene::CreditsScene(SDL_Renderer *renderer, Controller p1) : MenuScene(renderer,p1)
{
	loadBackground("Images/Backgrounds/credkts00713.bmp");
	moved = true;
	maxPos = 0;
	/*backgroundMusik.Initialize("Audio/Music/Prelude and Action.wav");
	backgroundMusik.Play();*/

	cursorPos[0].x = SCREEN_WIDTH / 100 * 37;
	cursorPos[0].y = SCREEN_HEIGHT / 100 * 72;

	cursorPos[1].x = SCREEN_WIDTH / 100 * 58;
	cursorPos[1].y = SCREEN_HEIGHT / 100 * 85;
}


CreditsScene::~CreditsScene()
{
}

int CreditsScene::Update()
{
	int res = MenuScene::Update();

	float dt = Scene::GetDeltaTime();

	if (res == 1)
	{
		return 1;
	}

	deltaTime += dt / 1000;

	if (deltaTime>= 0.1)
	{
		deltaTime = 0;
		curBackground++;
		if (curBackground > 2)
		{
			curBackground = 0;
		}

		switch (curBackground)
		{
		case 0: loadBackground("Images/Backgrounds/credkts00713.bmp"); break;
		case 1: loadBackground("Images/Backgrounds/font.bmp"); break;
		case 2: loadBackground("Images/Backgrounds/music.bmp"); break;
		default:
			break;
		}
	}

	return 5;
}