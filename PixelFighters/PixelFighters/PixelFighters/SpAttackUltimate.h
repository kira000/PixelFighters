#pragma once
#include "SpecialAttack.h"
class SpAttackUltimate :
	public SpecialAttack
{
public:
	SpAttackUltimate(SDL_Renderer* renderer, int screenWidth, int screenHeight, char* ultPath, int _width, int _height);
	~SpAttackUltimate();

	SpAttack Update(float dt, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* platforms, int nrMobs, int nrPlatforms);
	

	void CreateAttack(SDL_Rect startPos, int type, SDL_RendererFlip flip);

private:
	void loadImages(char* path);

	void move();

	/*SDL_Texture* texture;
	SDL_Rect* sprites;*/
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	int width;
	int height;

	bool hit = false;
	float frameChange;
	int frameChangeTimer = 200;

};

