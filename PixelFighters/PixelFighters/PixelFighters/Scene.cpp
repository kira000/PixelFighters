#include "Scene.h"


Scene::Scene( SDL_Renderer* renderer, Controller p1)
{
	
	_renderer = renderer;
	_p1 = p1;

	m_lnPerformanceFrequency = SDL_GetPerformanceFrequency();
	m_lnlastTime = m_lnNow = 0;
}

Scene::Scene(){}

Scene::~Scene()
{
	
//	SDL_DestroyTexture(background);
	_renderer = nullptr;
}

int Scene::Update(){ return 0; }

void Scene::Render(){}

float Scene::GetDeltaTime()
{
	m_lnNow = SDL_GetPerformanceCounter();
	double dt = double(m_lnNow - m_lnlastTime)*1000.0 / double(m_lnPerformanceFrequency);
	m_lnlastTime = m_lnNow;
	return (float)dt;
}