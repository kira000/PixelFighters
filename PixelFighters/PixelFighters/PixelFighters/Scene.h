#pragma once
#include <iostream>
#include <array>
#include "SDL.h"
#include "Controller.h"
#include "Character.h"
#include "macros.h"
#include "AudioSource.h"

enum class Backgrounds{Test};
//Struct for the Platform coordinates
typedef struct _Coordinates
{
	int x;
	int y;
	int w;
	int h;
	_Coordinates(int _x, int _y, int _w, int _h){ x = _x; y = _y; w = _w; h = _h; }
	_Coordinates(){ x = 0; y = 0; w = 0; h = 0; }
}Coordinates;

class Scene
{
public:
	Scene( SDL_Renderer* renderer, Controller p1);
	Scene();
	~Scene();
	virtual int Update();
	//RenderMethod
	virtual void Render();
	

protected:
	//current Window
	//Renderer
	SDL_Renderer* _renderer = nullptr;
	//SDL_Surface* background;
	SDL_Texture* background = nullptr;
	//Gamepad(Controller) for Player1
	Controller _p1;
	SDL_Rect rect;
	int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
	int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
	Uint64 m_lnlastTime;
	Uint64 m_lnNow;
	Uint64 m_lnPerformanceFrequency;

	float GetDeltaTime();

	AudioSource backgroundMusik;
	AudioClip anouncer;

};

