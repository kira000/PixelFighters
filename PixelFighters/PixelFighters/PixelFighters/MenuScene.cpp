#include "MenuScene.h"



MenuScene::MenuScene(SDL_Renderer *renderer, Controller p1) : Scene(renderer, p1)
{
	LoadCursorCorners();
	deltaTime = 0;
	moved = true;
	Scene::GetDeltaTime();
	change.Initialize("Audio/Effects/MenuEffects/Woosh-Mark_DiAngelo-4778593.wav");
	confirm.Initialize("Audio/Effects/MenuEffects/Tick-DeepFrozenApps-397275646.wav");
	backgroundMusik.Initialize("Audio/Music/Prelude and Action.wav");
	backgroundMusik.Play();
}


MenuScene::~MenuScene()
{
	backgroundMusik.Stop();
}


void MenuScene::Confirm()
{

}

void MenuScene::LoadCursorCorners()
{
	cursor = ImageControl::LoadAnimation(cursorPath, 0, cursorWidth, cursorHeight, 2, &cursorTexture, _renderer);
	cursorPos = new SDL_Rect();
	cursorPos[0].w = cursor[0].w * scale;
	cursorPos[0].h = cursor[0].h * scale;

	cursorPos[1].w = cursor[1].w * scale;
	cursorPos[1].h = cursor[1].h * scale;
	cursorPosition = 0;
}

int MenuScene::Update()
{
	float dt = Scene::GetDeltaTime();


	if (moved)
	{
		deltaTime += dt / 1000;
		if (deltaTime > 1)
		{

			deltaTime = 0;
			moved = false;
			return 0;
		}
	}

	if (!moved && _p1.IsConnected())
	{
		XINPUT_AXIS axis = _p1.getAxis();
		Button button = _p1.getButton();

		if (button == Button::ButtonA)
		{
			confirm.Play(false);
			//Confirm();
			return 1;
		}


		if (axis.sThumbLX != 0 || axis.sThumbLY)
		{
			moved = MoveCursor(axis, leftRight, upDown);
			if (moved)
			{
				change.Play(false);
			}
		}


	}

	return 0;
}

int MenuScene::Update(Controller p)
{
	float dt = Scene::GetDeltaTime();
	
	if (moved)
	{
		deltaTime += dt / 1000;
		if (deltaTime < 1)
		{	
			return 0;
		}
		else
		{
			deltaTime = 0;
			moved = false;
		}
	}

	if (p.IsConnected())
	{
		XINPUT_AXIS axis = p.getAxis();
		Button button = p.getButton();

		if (button == Button::ButtonA)
		{
			//Confirm();
			return 1;
		}

		if ((axis.sThumbLX != 0 || axis.sThumbLY != 0) && !moved)
		{
			moved = MoveCursor(axis, leftRight, upDown);
		}
		
	}

	return 0;
}

bool MenuScene::MoveCursor(XINPUT_AXIS axis, bool left, bool up)
{

	if (left)
	{
		if (axis.sThumbLX > 0)
		{
			//position.x += velocityX;
			cursorPosition++;
		}
		else if (axis.sThumbLX < 0)
		{
			cursorPosition--;
		}
		



		if (up)
		{
			if (axis.sThumbLY > 0)
			{
				//position.y -= velocityY;
				cursorPosition = 0;

			}
			else if (axis.sThumbLY < 0)
			{
				//position.y += velocityY;
				cursorPosition = 3;
			}
		}
	}
	else if (up)
	{
		if (axis.sThumbLY > 0)
		{
			//position.y -= velocityY;
			cursorPosition--;

		}
		else
		{
			//position.y += velocityY;
			cursorPosition++;
		}
	}

	if (cursorPosition > maxPos)
	{
		cursorPosition = maxPos - 1;
	}

	if (cursorPosition < 0)
	{
		cursorPosition = 0;
	}

	return true;
}


void MenuScene::loadBackground(char* path)
{
	SDL_Surface *surface = SDL_LoadBMP(path);
	if (surface == NULL)
	{
		printf("Failed to load surface: %s", SDL_GetError());
	}
	background = SDL_CreateTextureFromSurface(_renderer, surface);
	if (background == NULL)
	{
		printf("Failed to load background: %s", SDL_GetError());
	}

	//SAFE_DELETE(surface);
}

void MenuScene::Render(bool present)
{
	SDL_RenderCopy(_renderer, background, NULL, NULL);

	for (int i = 0; i < 2; i++)
	{
		SDL_RenderCopy(_renderer, cursorTexture, &cursor[i], &cursorPos[i]);
	}

	if (present)
	{
		SDL_RenderPresent(_renderer);

	}
}