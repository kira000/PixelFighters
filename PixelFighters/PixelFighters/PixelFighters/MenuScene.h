#pragma once

#include "Scene.h"

class MenuScene :
	public Scene
{
public:
	MenuScene(SDL_Renderer *renderer, Controller p1);
	~MenuScene();
	bool MoveCursor(XINPUT_AXIS, bool left, bool up);
	void Confirm();
	int Update();
	int Update(Controller p);
	void Render(bool present);
	void LoadCursorCorners();

protected:

	void loadBackground(char* path);

	int velocityX;
	int velocityY;

	SDL_Rect position;

	SDL_Rect *cursor;
	SDL_Rect *cursorPos;



	int cursorPosition;
	float deltaTime = 0;

	bool moved;
	
	int maxPos;

	char* cursorPath = "Images/Backgrounds/cursor.bmp";

	int cursorWidth = 4;
	int cursorHeight = 4;

	SDL_Texture *cursorTexture;

	int scale = 5;

	bool leftRight = false;
	bool upDown = false;
	AudioClip change;
	AudioClip confirm;

};

