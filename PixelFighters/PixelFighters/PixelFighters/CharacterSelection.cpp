#include "CharacterSelection.h"


CharacterSelection::CharacterSelection(SDL_Renderer *renderer, Controller p1, Controller p2) : MenuScene(renderer, p1)
{
	loadBackground("Images/Backgrounds/choose.bmp");
	maxPos = 5;
	upDown = true;
	leftRight = true;
	_p2 = p2;
	cursorPosition = 0;
	moved = true;
	deltaTime = 0;
	
	anouncer.Initialize("Audio/Effects/Ansager/ChooseYourFate.wav");
	anouncer.Play(false);
}


CharacterSelection::~CharacterSelection()
{
	SDL_DestroyTexture(background);
	background = nullptr;
	_renderer = nullptr;
	
}

int CharacterSelection::Update(ChosenFighters &selection)
{
	
	/*selection.fighter2 = Fighters::Warrior;
	loadChosenFighter(Fighters::Warrior, 1);*/
	int res = -1;
	if (selection.fighter1 == Fighters::No || selection.fighter2 != Fighters::No)
	{
		_p1.GetState();
		res = MenuScene::Update(_p1);
	}
	else
	{
		_p2.GetState();
		res = MenuScene::Update(_p2);
	}

	setCursor();
	int choiseNr = 0;

	if (selection.fighter1 == Fighters::No)
	{
		choiseNr = 0;
	}
	else
	{
		choiseNr = 1;
	}

	if (res == 1)
	{
		switch (cursorPosition)
		{
		case 0: if (selection.fighter1 == Fighters::No)
				{
					selection.fighter1 = Fighters::Master;
					fighterChosen.Initialize("Audio/Effects/Characters/Sensei/Intro.wav");
					fighterChosen.Play(false);
					
				}
				else if (selection.fighter2 == Fighters::No)
				{
					selection.fighter2 = Fighters::Master; 	
					fighterChosen.Initialize("Audio/Effects/Characters/Sensei/Intro.wav");
					fighterChosen.Play(false);
				} 
				

				loadChosenFighter(Fighters::Master,choiseNr);
				break;
		case 1: if (selection.fighter1 == Fighters::No)
				{
					selection.fighter1 = Fighters::Thing;
					fighterChosen.Initialize("Audio/Effects/Characters/Morphaust/Intro.wav");
					fighterChosen.Play(false);
				}
				else if (selection.fighter2 == Fighters::No)
				{
					selection.fighter2 = Fighters::Thing;
					fighterChosen.Initialize("Audio/Effects/Characters/Morphaust/Intro.wav");
					fighterChosen.Play(false);
				} 
				

				loadChosenFighter(Fighters::Thing, choiseNr);
				break;
		case 2: if (selection.fighter1 == Fighters::No)
				{
					selection.fighter1 = Fighters::Warrior;
					fighterChosen.Initialize("Audio/Effects/Characters/Ninja/Intro.wav");
					fighterChosen.Play(false);
				}
				else if (selection.fighter2 == Fighters::No)
				{
					selection.fighter2 = Fighters::Warrior;
					fighterChosen.Initialize("Audio/Effects/Characters/Ninja/Intro.wav");
					fighterChosen.Play(false);
				} 
				
				
				loadChosenFighter(Fighters::Warrior, choiseNr);
				break;
		case 3:  return 1; break;
		case 4: if (selection.fighter1 != Fighters::No && selection.fighter2 != Fighters::No)
					{
					backgroundMusik.Stop();
						return 3;
					}
		default:
			break;
		}
		/*if (selection.fighter1 != Fighters::No && selection.fighter2!=Fighters::No)
		{
			cursorPosition = 4;
		}*/
	}

	return 2;

}

void CharacterSelection::RenderChoise(ChosenFighters &fighters)
{
	RenderPos[0] = choise[0];
	RenderPos[1] = choise[1];
	if (fighters.fighter1 != Fighters::No)
	{
		RenderPos[0].w = choise[0].w * scale;
		RenderPos[0].h = choise[0].h * scale;
		RenderPos[0].x = SCREEN_WIDTH / 100 * 10;
		RenderPos[0].y = SCREEN_HEIGHT / 100 * 35;

	}

	if (fighters.fighter2 != Fighters::No)
	{
		RenderPos[1].w = choise[1].w * scale;
		RenderPos[1].h = choise[1].h * scale;


		RenderPos[1].y = SCREEN_HEIGHT / 100 * 30;
		RenderPos[1].x = SCREEN_WIDTH / 100 * 90;
	}


	if (choiseText[0]!=nullptr)
	{
		ImageControl::Render(&RenderPos[0], choiseText[0], _renderer, &choise[0], 0, SDL_FLIP_NONE);
	}

	if (choiseText[1] != nullptr)
	{
		ImageControl::Render(&RenderPos[1], choiseText[1], _renderer, &choise[1], 0, SDL_FLIP_NONE);
	}
}

void CharacterSelection::setCursor()
{
	if (cursorPosition < 3)
	{
		cursorPos[0].y = SCREEN_HEIGHT / 100 * 37;
		cursorPos[1].y = SCREEN_HEIGHT / 100 * 59.5;
	}
	else
	{
		cursorPos[0].y = SCREEN_HEIGHT / 100 * 72.2;
		cursorPos[1].y = SCREEN_HEIGHT / 100 * 84;
	}

	

	switch (cursorPosition)
	{
	case 0: cursorPos[0].x = SCREEN_WIDTH / 100 * 38; cursorPos[1].x = SCREEN_WIDTH / 100 * 43; break;
	case 1: cursorPos[0].x = SCREEN_WIDTH / 100 * 44.5; cursorPos[1].x = SCREEN_WIDTH / 100 * 50; break;
	case 2: cursorPos[0].x = SCREEN_WIDTH / 100 * 51; cursorPos[1].x = SCREEN_WIDTH / 100 * 57; break;
	case 3: cursorPos[0].x = SCREEN_WIDTH / 100 * 37; cursorPos[1].x = SCREEN_WIDTH / 100 * 47; break;
	case 4: cursorPos[0].x = SCREEN_WIDTH / 100 * 47.7; cursorPos[1].x = SCREEN_WIDTH / 100 * 57.7; break;
	default:
		break;
	}

}

void CharacterSelection::loadChosenFighter(Fighters chosen, int choiseNr)
{
	switch (chosen)
	{
	case Fighters::Warrior: choise[choiseNr] = *ImageControl::LoadAnimation("Images/Characters/Warrior.bmp", 0, 65, 65, 1, &choiseText[choiseNr], _renderer);
		break;
	case Fighters::Master: choise[choiseNr] = *ImageControl::LoadAnimation("Images/Characters/Master.bmp", 0, 65, 65, 1, &choiseText[choiseNr], _renderer);
		break;
	case Fighters::Thing: choise[choiseNr] = *ImageControl::LoadAnimation("Images/Characters/Thing.bmp", 0, 65, 65, 1, &choiseText[choiseNr], _renderer);
		break;
	case Fighters::No:
		break;
	default:
		break;
	}
	

}

void CharacterSelection::Render(ChosenFighters &fighters)
{
	MenuScene::Render(false);
	RenderChoise(fighters);
	SDL_RenderPresent(_renderer);
}