#include "FightScene.h"



//Const
FightScene::FightScene(SDL_Renderer* renderer, Controller p1, Controller p2, ChosenFighters fighters) : Scene(renderer, p1)
, char1(renderer, SCREEN_WIDTH, SCREEN_HEIGHT)
, char2(renderer, SCREEN_WIDTH, SCREEN_HEIGHT)
{
	//hud = new HUD(renderer);

	_p2 = p2;

	//Rect für Hintergrund erstellen
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;

	//Platformen erstellen
	setPlatformCoordinates();

	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	loadImages();

	createPlatforms(currentBckg);
	//Sleep(100);

	//Charactere erstellen

	char2.createFighters(fighters.fighter2, 1);
	char1.createFighters(fighters.fighter1, 0);

	backgroundMusik.Initialize("Audio/Music/Future Gladiator.wav");
	backgroundMusik.Play();

	createMob();

	victory = *ImageControl::LoadAnimation("Images/Backgrounds/Victory.bmp", 0, 80, 40, 1, &victoryText, renderer);

	victoryPos = victory;
	victoryPos.x = SCREEN_WIDTH / 100 * 50 - 40;
	victoryPos.y = SCREEN_HEIGHT / 100 * 50 - 20;
	anouncer.Initialize("Audio/Effects/Ansager/Fight.wav");
	anouncer.Play(false);
}

//Dest
FightScene::~FightScene()
{
	

	mobs.clear();

	SDL_DestroyTexture(platform1);
	platform1 = nullptr;
	backgroundPath = nullptr;
	platformPath1 = nullptr;
	
	platformRects = nullptr;
	_renderer = nullptr;
}




//Update Method
int FightScene::Update(){

	//wenn pause
	//->Screen ausführen
	//return;

	//calculate deltatime
	float dt = Scene::GetDeltaTime();

	//add dt to timer
	deltaTime += dt / 1000;

	//normal Attack P1
	StAttack attackP1;
	//normal Attack P2
	StAttack attackP2;

	//special Attack P1
	SpAttack spattackP1;
	//special Attack P2
	SpAttack spattackP2;

	//Clear screen
	//SDL_RenderClear(_renderer);
	//initialize button for input
	Button button = Button::None;
	//initialize axis for input
	XINPUT_AXIS axis = *new XINPUT_AXIS();

	//initialize damage p1
	int p1Damage = 0;
	//initialize damage p2
	int p2Damage = 0;

	//initialize energygroth p1
	int p1EnergyGain = 0;
	//initialize energygroth p2
	int p2EnergyGain = 0;

	//initialize rect array
	SDL_Rect* mobRects = new SDL_Rect[mobs.size()];

	int cnt = 0;

	for each (Mob* mob in mobs)
	{
		mobRects[cnt] = mob->position;
		cnt++;
	}

	//check Input player1
	if (_p1.IsConnected()) //p1 is connected
	{
		_p1.GetState();//read Gamepad
		button = _p1.getButton();//get button
		axis = _p1.getAxis(); //get the axes


		if (button == Button::Back)
		{
			//SDL_RenderPresent(_renderer);
			SDL_RenderClear(_renderer);
			backgroundMusik.Stop();
			return 1;
		}
	}
	attackP1 = char1.Update(dt, button, axis, &char2.currentPos, mobRects, platformRects, mobs.size(), nrPlatforms);

	button = Button::None;
	axis = *new XINPUT_AXIS();

	//analog zu p1
	if (_p2.IsConnected())
	{
		_p2.GetState();
		button = _p2.getButton();
		axis = _p2.getAxis();


		if (button == Button::Back)
		{
			//SDL_RenderPresent(_renderer);
			SDL_RenderClear(_renderer);
			backgroundMusik.Stop();
			return 1;
		}
	}



	//Hintergrund zeichnen
	Render();

	attackP2 = char2.Update(dt, button, axis, &char1.currentPos, mobRects, platformRects, nrMobs, nrPlatforms);

	//Mögliche Spezialattacken updaten
	spattackP1 = char1.UpdateSpecial(&char2.currentPos, mobRects, platformRects, mobs.size(), nrPlatforms);
	spattackP2 = char2.UpdateSpecial(&char1.currentPos, mobRects, platformRects, mobs.size(), nrPlatforms);

	//Update taken damage for normal attacks

	EnergyValues p2Val = updateDamage(attackP1, &char1, &char2);
	EnergyValues p1Val = updateDamage(attackP2, &char2, &char1);

	//Update taken damage for special attacks
	p2Val += updateDamage(spattackP1, &char1, &char2);
	p1Val += updateDamage(spattackP2, &char2, &char1);

	list<Mob*> mobsA = mobs;

	for each (Mob* mob in mobsA)
	{
		if (mob->Update(platformRects, nrPlatforms, dt))
		{
			destroyMob(mob);
		}
	}

	/*for each (Mob* var in mobsA)
	{
	destroyMob(var);
	}*/



	//if timer > spawnTime
	if (deltaTime >= mobSpawnTime)
	{
		//reset timer
		deltaTime = 0;
		//create new mob
		createMob();
	}

	nrMobs = mobs.size();
	


	//Update takenn damage of player1
	if (char1.live <= 10 && !char2.IsUlt())
	{
		p1Val.damage = 0;
	}
	char1.UpdateDamage(p1Val.damage, p2Val.energy);

	//Update takenn damage of player2
	if (char2.live <= 10 && !char1.IsUlt())
	{
		p2Val.damage = 0;
	}
	char2.UpdateDamage(p2Val.damage, p1Val.energy);

	//Render Specialattack p1
	char1.RenderSpecial();
	//Render Specialattack p2
	char2.RenderSpecial();


	//delay between runs
	Sleep(10);




	//Wenn p1 keine leben mehr hat
	if (char1.live <= 0)
	{
		winDelta += dt;
		printf("p1 besiegt \n");
		//ToDo
		//Aufruf WinScreen mit p2 Sieger
		SDL_RenderCopy(_renderer, victoryText, &victory, &victoryPos);
		if (!victoryPlayed)
		{
			anouncer.Initialize("Audio/Effects/Ansager/Fight.wav");
			anouncer.Play(false);
			victoryPlayed = true;
		}

		if (winDelta >= 10)
		{
			backgroundMusik.Stop();
			return 1;
		}
	}
	if (char2.live <= 0)
	{
		winDelta += dt;
		printf("p2 besiegt \n");
		//	//ToDo
		//	//Aufruf WinScreen mit p1 Sieger

		SDL_RenderCopy(_renderer, victoryText, &victory, &victoryPos);
		if (!victoryPlayed)
		{
			anouncer.Initialize("Audio/Effects/Ansager/Fight.wav");
			anouncer.Play(false);
			victoryPlayed = true;
		}
		if (winDelta >= 10)
		{
			//	return 1;
			backgroundMusik.Stop();
			return 1;
		}
	}
	//Rendern
	SDL_RenderPresent(_renderer);

	SDL_RenderClear(_renderer);

	

	return 3;

}

//RenderMethod
void FightScene::Render(){
	//ToDo
	//Draw Background
	//SDL_BlitScaled(background, NULL, _screenSurface, NULL);
	SDL_RenderCopy(_renderer, background, NULL, NULL);
	//draw platforms

	drawPlatforms();

}

//Gets the Images for the stage
void FightScene::loadImages(){
	//ToDo
	//load background
	//printf("%s", backgroundPath.c_str());
	//Hintergrund laden
	background = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(backgroundPath));
	if (background == NULL)
	{
		printf("Failed to load background: %s", SDL_GetError());
	}
	//Enum Setzen(Debugversion)
	currentBckg = Backgrounds::Test;


	//load platform image(s)
	platform1 = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(platformPath1));
	/*platform2 = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(platformPath2));
	platform3 = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(platformPath3));
	platform4 = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(platformPath4));
	platform5 = SDL_CreateTextureFromSurface(_renderer, SDL_LoadBMP(platformPath5));*/
	/*if (platform == NULL)
	{
	printf("Failed to load platform: %s", SDL_GetError());
	}*/
}

void FightScene::createPlatforms(Backgrounds background)
{
	//Initialisierungen
	SDL_Rect rect;
	Coordinates* platformCoordinates = NULL;

	//Level anhand des Hintergrunds erstellen
	switch (background)
	{
	case Backgrounds::Test: nrPlatforms = 6; platformCoordinates = testCoord; break;
	default:
		break;
	}

	//Platformpositionen erstellen
	for (int i = 0; i < nrPlatforms; i++)
	{
		//Coordinaten setzen
		rect.x = platformCoordinates[i].x;
		rect.y = platformCoordinates[i].y;
		rect.w = platformCoordinates[i].w;
		rect.h = platformCoordinates[i].h;
		//In Array registrieren
		platformRects[i] = rect;
	}
}

void FightScene::drawPlatforms()
{
	//Für jede Platform im array
	for (int i = 1; i < nrPlatforms; i++)
	{
		drawPlatform(platformRects[i]);
	}
}

void FightScene::drawPlatform(SDL_Rect rect)
{
	//SDL_BlitScaled(platform, NULL, _screenSurface, &rect);
	SDL_RenderCopy(_renderer, platform1, NULL, &rect);
}

void FightScene::setPlatformCoordinates()
{
	float width1Perc = SCREEN_WIDTH / 100;
	float height1Perc = SCREEN_HEIGHT / 100;

	//Koordinatenarrays für mögliche Stages erstellen
	testCoord[0] = Coordinates(0, height1Perc * 91, SCREEN_WIDTH, height1Perc * 20);
	testCoord[1] = Coordinates(width1Perc * 1, height1Perc * 73, width1Perc * 23, height1Perc * 3);
	testCoord[2] = Coordinates(width1Perc * 10, height1Perc * 45, width1Perc * 50, height1Perc * 3);
	testCoord[3] = Coordinates(width1Perc * 3, height1Perc * 20, width1Perc * 20, height1Perc * 3);
	testCoord[4] = Coordinates(width1Perc * 72, height1Perc * 20, width1Perc * 20, height1Perc * 3);
	testCoord[5] = Coordinates(width1Perc * 80, height1Perc * 71, width1Perc * 20, height1Perc * 3);
}


void FightScene::createMob()
{

	try{
		//if nr of mobs < 10
		if (mobs.size() < 10)
		{
			//create new mob

			Mob *mob = new Mob(_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

			//set position
			mob->position.x = SCREEN_WIDTH / 2;
			mob->position.y = 20;

			//add mob at end of vector

			
			if (mob != nullptr)
			{
				mobs.push_back(mob);
			}
			
			//SAFE_DELETE(mob);
		}

	}
	catch (...)
	{
		printf("Fehler beim erstellen eines Gegners\nund dieser catch ist absolut nutzlos, da push_back() die Exception nicht weitergiebt");
	}


	//save size of vector
	nrMobs = mobs.size();

}

void FightScene::destroyMob(Mob* mob)
{

	mobs.remove(mob);
	SAFE_DELETE(mob);

}


EnergyValues FightScene::updateDamage(StAttack attack, Character* attacking, Character* hit)
{
	int damage = 0;
	int energy = 0;
	for (int i = 0; i < attack.nrHits; i++)
	{
		//Wenn Hit = spieler 2
		if (attack.hits[i].x == hit->currentPos.x && attack.hits[i].y == hit->currentPos.y)
		{
			//Spieler2 Schaden zufügen
			//char2->UpdateDamage(attackP1.damage, 0);
			damage += attack.damage;
			energy += 2;
		}
		else
		{
			for each (Mob* mob in mobs)
			{
				if (attack.hits[i].x == mob->position.x && attack.hits[i].y == mob->position.y)
				{
					if (attack.damage >= 0 && mob->getLife() >= 0)
					{
						energy += mob->takeDamage(attack.damage);
					}
				}
			}
		}
	}

	return EnergyValues(damage, energy);
}
EnergyValues FightScene::updateDamage(SpAttack attack, Character* attacking, Character* hit)
{
	int damage = 0;
	int energy = 0;

	for (int i = 0; i < attack.nrHits; i++)
	{
		//Wenn Hit = spieler 2
		if (attack.hits[i].x == hit->currentPos.x && attack.hits[i].y == hit->currentPos.y)
		{
			//Spieler2 Schaden zufügen
			//char2->UpdateDamage(attackP1.damage, 0);
			damage += attack.damage;
			energy += 5;
		}
		else
		{
			for each (Mob* mob in mobs)
			{
				if (mob != nullptr)
				{
					if (attack.hits[i].x == mob->position.x && attack.hits[i].y == mob->position.y)
					{
						if (attack.damage > 0 && mob->getLife() >= 0)
						{
							energy += mob->takeDamage(attack.damage);
						}
					}
				}
			}
		}
	}

	return EnergyValues(damage, energy);
}
