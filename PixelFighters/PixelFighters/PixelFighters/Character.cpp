#include "Character.h"
#include "Controller.h"
#include "ImageControl.h"



Character::Character(SDL_Renderer* renderer, int screenWidth, int screenHeight) : _hud(renderer,screenWidth,screenHeight)
{
	//Initialisierung der Charactere

	_renderer = renderer;

	//energy = maxEnergy;

	spAttck = new SpecialAttack();
	spRound = new SpRound(renderer, screenWidth, screenHeight);
	spFollow = new SpFollow(renderer, screenWidth, screenHeight);
	spAttackLine = new SpAttackLine(renderer, screenWidth, screenHeight); //Debugvalue

	jumpSound.Initialize("Audio/Effects/MoveSounds/Mario_Jumping-Mike_Koenig-989896458.wav");
	punchSound.Initialize("Audio/Effects/MoveSounds/AttackSounds/Standart/Jab-SoundBible.com-1806727891.wav");
	kickSound = punchSound;
}

Character::Character(){}

Character::~Character()
{

	SAFE_DELETE(spAttackLine);
	SAFE_DELETE(spRound);
	SAFE_DELETE(spFollow);
	SAFE_DELETE(spUlt);
	//SAFE_DELETE(spAttck);

	SAFE_DELETE(_Walk);

	SAFE_DELETE(_Punch);
	SAFE_DELETE(_Kick);

	SAFE_DELETE(_Jump);
	SAFE_DELETE(_Block);
	SAFE_DELETE(_Damage);

	SAFE_DELETE(_Vanish);
	SAFE_DELETE(_Appear);

	SDL_DestroyTexture(texture);

	//SAFE_DELETE(_hud);

	ultpath = nullptr;

	_renderer = nullptr;

}

void Character::LoadSprites(char* charpath)
{
	//Aufruf statische Methode zum Auslesen der Sprites
	_Idle = *ImageControl::LoadAnimation(charpath, 0, charWidth, charHeight, 1, &texture, _renderer);
	_Walk = ImageControl::LoadAnimation(charpath, 1, charWidth, charHeight, 8, &texture, _renderer); //Beim debuggn besonders beachten^^
	_Kick = ImageControl::LoadAnimation(charpath, 2, charWidth, charHeight, 8, &texture, _renderer);
	_Punch = ImageControl::LoadAnimation(charpath, 3, charWidth, charHeight, 8, &texture, _renderer);
	_Block = ImageControl::LoadAnimation(charpath, 4, charWidth, charHeight, 8, &texture, _renderer);
	_Jump = ImageControl::LoadAnimation(charpath, 5, charWidth, charHeight, 8, &texture, _renderer);
	_Damage = ImageControl::LoadAnimation(charpath, 6, charWidth, charHeight, 1, &texture, _renderer);
	_Vanish = ImageControl::LoadAnimation(charpath, 7, charWidth, charHeight, 8, &texture, _renderer);
	_Appear = ImageControl::LoadAnimation(charpath, 8, charWidth, charHeight, 8, &texture, _renderer);
}

void Character::createFighters(Fighters fighter, int playerNr) 
{
	int hudnr = 0;
	//SpriteSheetPfad für Kämpfer auslesen
	switch (fighter)
	{
	case Fighters::Warrior: charWidth = 70; charHeight = 70; LoadSprites("Images/Characters/Warrior.bmp"); hudnr = 2;
		ultpath = "Images/Attacks/Specials/WarriorFinisher.bmp";
		spUlt = new SpAttackUltimate(_renderer, screenWidth, screenHeight, ultpath, 236, 70);
		ultType = 2;
		UltAttackSound.Initialize("Audio/Effects/Characters/Ninja/Finisher.wav");
		


		break;
	case Fighters::Master: charWidth = 66; charHeight = 66; LoadSprites("Images/Characters/Master.bmp"); hudnr = 1;
		ultpath = "Images/Attacks/Specials/MasterFinisher.bmp";
		spUlt = new SpAttackUltimate(_renderer, screenWidth, screenHeight, ultpath, 500, 500);
		ultType = 1;
		UltAttackSound.Initialize("Audio/Effects/Characters/Sensei/Finisher.wav");
		break;
	case Fighters::Thing: charWidth = 62; charHeight = 62; LoadSprites("Images/Characters/Thing_advanced.bmp"); hudnr = 0;
		ultpath = "Images/Attacks/Specials/pullmyfinger.bmp";
		spUlt = new SpAttackUltimate(_renderer, screenWidth, screenHeight, ultpath, 150, 150);
		//ultpath = "Images/Characters/Thing_advanced.bmp";
		ultType = 0;
		UltAttackSound.Initialize("Audio/Effects/Characters/Morphaust/Finisher.wav");
		break;
	default:
		break;
	}

	_hud.setNumbers(playerNr, hudnr);

	



	charWidth *= scale;
	charHeight *= scale;

	if (playerNr == 0)
	{
		flip = SDL_FLIP_NONE;
		currentPos.x = (screenWidth / 100) + charWidth;
		currentPos.y = (screenHeight / 100 * 60);
		currentPos.w = charWidth;
		currentPos.h = charHeight;

	}
	else
	{
		flip = SDL_FLIP_HORIZONTAL;
		currentPos.x = (screenWidth - charWidth);
		currentPos.y = (screenHeight / 100 * 60);
		currentPos.w = charWidth;
		currentPos.h = charHeight;

	}
	_playerNr = playerNr;

}


StAttack Character::Update(float _dt, Button pressed, XINPUT_AXIS axis, SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* Platforms, int mobCount, int platformCount)
{
	dt = _dt;
	//ToDo:
	//Zurücksetzen des Timers für AttackLevels nach Zeit
	attack.damage = 0;
	if (isVanishing)
	{
		Vanish();
		return StAttack();
	}

	if (isAppearing && !spAttck->IsActive())
	{
		if (ultType == 1)
		{
			Vanish();
			return StAttack();
		}
		Appear();
		return StAttack();
	}

	//Unterscheidung der Eingaben
	spTimer += dt;

	if (axis.bRightTrigger > 0)
	{
		blockFinished = false;
		Block(true);
		AddGravity();
		collisionDetection(Platforms, platformCount, true);
		//SAFE_DELETE(ahits);
		return StAttack();

	}
	if (blockFinished == true)
	{
		Block(false);
		AddGravity();
		collisionDetection(Platforms, platformCount, true);
		//SAFE_DELETE(ahits);
		return StAttack();

	}
	blocking = false;

	if (spTimer > maxSpTime)
	{
		spTimer = 0;
		attackLevel = 0;
	}

	printf("%d\n", attackLevel);
	switch (pressed)
	{
	case Button::ButtonA:  if (!airborne) jumping = true; break;
	case Button::ButtonB:  punch = true; break;
	case Button::ButtonY:  kick = true; break;
	case Button::ButtonX: if (attackLevel < 4){
							  if (!lvlRaised){ attackLevel++; lvlRaised = true; spTimer = 0; }
	}
	default:
		break;
	}

	if (lvlRaised)
	{
		if (spTimer > spLvlRaisedTime)
		{
			lvlRaised = false;
		}
	}

	//Wenn Sprungtaste gedrückt + Character am Boden
	if (jumping && !airborne)
	{
		//Spring
		Jump();
	}

	//attackLevel = 3;
	//Wenn Schlag gedrückt
	if (attackLevel == 0)
	{
		if (punch)
		{
			//Schlag
			Punch(mobs, enemy, mobCount);
		}

		//Wenn Tritt gedrückt
		if (kick)
		{
			//Tritt
			Kick(mobs, enemy, mobCount);
		}
	}
	else
	{
		if (punch || kick)
		{
			switch (attackLevel)
			{
			case 1:if (energy >= costLow)
			{
					   SDL_Rect pos = currentPos;
					   pos.x -= pos.w / 2;
					   pos.y -= pos.h / 2;
					   attackHeight = 1;
					   spRound->CreateAttack(flip, pos); spAttck = spRound; CalcEnergy(-costLow);
					   spAttck->attackSound.Play(false);
					   playerFreeze = true;
					   roundFollow = true;
			}break;
			case 2:if (energy >= costMiddle)
			{
					   attackHeight = 2;
					   spAttackLine->CreateAttack(flip, currentPos); spAttck = spAttackLine;  CalcEnergy(-costMiddle);
					   spAttck->attackSound.Play(false);

			} break;
			case 3:
				if (energy >= costHigh)
				{
					attackHeight = 3;
					spFollow->CreateAttack(flip, *enemy); spAttck = spFollow;  CalcEnergy(-costHigh);
					spAttck->attackSound.Play(false);
					roundFollow = true;

				}
				break;
			case 4: if (energy >= costUltimate)
			{
						SDL_Rect startPos;

						switch (ultType)
						{
						case 0: startPos = *enemy;
							startPos.y = 0; break;
						case 1:
						case 2: startPos = currentPos; break;

						default:
							break;
						}


						isVanishing = true;
						isUlt = true;
						attackHeight = 4;
						UltAttackSound.Play(false);
						spUlt->CreateAttack(startPos, ultType, flip); spAttck = spUlt, CalcEnergy(-costUltimate);

			} break;
			default:
				break;
			}

			punch = false;
			kick = false;
			attackLevel = 0;
		}

	}

	//Wenn Analogstick bewegt + kein Schlag + kein Tritt
	if (axis.sThumbLX != 0 && !punch && !kick &&!playerFreeze)
	{
		//Lauf
		Walk(axis);
		move = true;
	}
	else
	{
		move = false;
	}

	//Wenn keinerlei Bewegung
	if (!punch && !kick && !move)
	{
		//Idleanimation
		current = _Idle;
	}

	//Wenn nicht gesprungen wird
	if (!jumping)
	{
		//Gravitation hinzufügen
		AddGravity();
	}

	//Kollisionsabfrage
	collisionDetection(Platforms, platformCount, true);
	//statische Methode zum Rendern
	//SAFE_DELETE(ahits);


	//Rückgabe AttackStruct
	return attack;

}


SpAttack Character::UpdateSpecial(SDL_Rect* enemy, SDL_Rect* mobs, SDL_Rect* Platforms, int mobCount, int platformCount)
{
	spattack.hits = nullptr;
	spattack.nrHits = 0;
	//Wenn eine Attacke aktiv ist
	if (spAttck->IsActive() && !isVanishing)
	{
		if (isUlt)
		{
			if (ultpath != "Images/Attacks/Specials/pullmyfinger.bmp")
			{
				if (ultpath == "Images/Attacks/Specials/WarriorFinisher.bmp")
				{
					current = _Vanish[2];
				}
				else
				{
					current = _Vanish[3];
				}

			}
			else
			{
				current = _Vanish[7];
			}

		}
		//Aufruf Update  Spezialatacke

		spattack = spAttck->Update(dt, enemy, mobs, Platforms, mobCount, platformCount);

		if (!spAttck->IsActive() && isUlt)
		{
			spriteNr = 0;
			isUlt = false;
			if (ultType == 0)
			{
				isAppearing = true;
			}
		}
		else if (!spAttck->IsActive() && roundFollow)
		{
			spAttck->hitSound.Play(false);
			roundFollow = false;
		}
	}
	else
	{
		playerFreeze = false;
		attackHeight = 0;
	}
	//rückgabe spattack werte
	return spattack;
}

void Character::UpdateDamage(int damage, int Energy)
{

	//Aufruf Lebensberechnung
	if (!blocking)
	{
		if (damage > 0)
		{
			damageTiming += dt;
			current = *_Damage;
			CalcLife(damage);
		}

	}

	if (damageTiming != 0)
	{
		damageTiming += dt;
		current = *_Damage;
		if (damageTiming >= 100)
		{
			damageTiming = 0;
		}
	}

	//Aufruf Energieberechnung
	CalcEnergy(Energy);

	ImageControl::Render(&currentPos, texture, _renderer, &current, 0, flip);
	_hud.Update(live, energy, attackLevel, attackHeight);
}

bool Character::Block(bool block)
{
	if (block)
	{
		if (jumping)
		{
			jumping = false;
			airborne = true;

		}
		blockFrameChange += dt;
		if (blockFrameChange > blockAnimationTimer)
		{
			blockFrameChange = 0;

			if (spriteNr == 4)
			{
				blocking = true;
			}
			else
			{
				spriteNr++;
			}
		}
		current = _Block[spriteNr];
		return false;
	}
	else
	{
		blockFrameChange += dt;
		if (blockFrameChange > blockAnimationTimer)
		{
			blockFrameChange = 0;
			spriteNr++;
		}
		if (spriteNr < 8)
		{
			current = _Block[spriteNr];
		}
		else
		{
			blockFrameChange = 0;
			blocking = false;
			return true;
		}
	}
	return false;
}

void Character::Walk(XINPUT_AXIS axis)
{
	//Timer erhöhen
	walkFrameChange += dt;

	//Wenn die Anzeigzeit überschritten ist
	if (walkFrameChange > timeWalkFrame)
	{
		//Sprite weiterschalten
		spriteNr++;
		//Wenn maximalanzahl 
		if (spriteNr > 7)
		{
			//Auf 1. Frame zurücksetzen
			spriteNr = 0;

		}
		//Timer zurücksetzen
		walkFrameChange = 0;
	}


	//wenn nicht in der Luft
	if (!jumping && !airborne)
	{
		//aktueller Frame = entsprechendes WalkFrame 
		current = _Walk[spriteNr];
	}

	//prüfen ob Stick nach rechts geneigt ist
	if (axis.sThumbLX > 0)
	{
		//Bewegung in Ricchtung
		currentPos.x += walkSpeed;
		flip = SDL_FLIP_NONE;
	}
	else
	{
		//Bewegung zurücksetzen
		currentPos.x -= walkSpeed;
		flip = SDL_FLIP_HORIZONTAL;
	}

	//prüfen ob linker rand überschritten wurde
	if (currentPos.x <= 0)
	{
		//an linken Rand setzen
		currentPos.x += walkSpeed;
	}
	//prüfen ob recher rand überschritten wurde 
	if (currentPos.x + currentPos.h >= screenWidth)
	{
		//an rechten rand setzen
		currentPos.x -= walkSpeed;
	}
}

void Character::Jump()
{

	//wenn nicht in der luft
	if (!airborne)
	{
		//jumptimer erhöhen
		jumpDuration += dt;
		jumpFrameChange += dt;
		if (jumpFrameChange > jumpAnimationTimer)
		{
			if (spriteNr == 0)
			{
				jumpSound.Play(false);
			}
			jumpFrameChange = 0;
			if (spriteNr <= 4)
			{
				spriteNr++;
			}
			current = _Jump[spriteNr];
		}
		//wenn dauer des Sprungs kleiner als höher
		if (jumpDuration < jumpHeight)
		{
			//Sprite nach oben setzen
			currentPos.y -= jumpSpeed;
		}


		//sonst
		else
		{
			//Character springt nicht und ist in der luft
			jumping = false;
			airborne = true;

			//Sprungdauer zurücksetzen
			jumpDuration = 0;
		}
	}

}

void Character::Punch(SDL_Rect* mobs, SDL_Rect* enemy, int mobCount)
{
	//Initialisierungen
	attack.hits = new SDL_Rect();
	hitcount = 0;

	SDL_Rect* hits = new SDL_Rect();

	//Schlagtimer erhöhen
	punchFrameChange += dt;

	//Wenn Timer höher Zeit
	if (punchFrameChange > punchTimer)
	{
		//Nr erhöhen
		spriteNr++;

		//Wenn Spritenr größer max
		if (spriteNr > 7)
		{
			//Spritenr zurücksetzen
			spriteNr = 0;
			// Schlag falsch
			punch = false;
		}
		//Timer zurücksetzen
		punchFrameChange = 0;

		//Wenn der 6.Sprite erreicht ist 
		if (spriteNr == 5)
		{
			punchSound.Play(false);
			//Getroffenen Gegenstände 
			hits = collisionDetection(mobs, mobCount, false);
			//SAFE_DELETE(ahits);
			//Wenn ein Gegner vorhanden ist
			if (enemy != nullptr)
			{
				//Wenn Gegner getroffen wurde
				if (checkCollision(*enemy))
				{
					//Gegener wird zu Trefferliste hinzugefügt
					hits[hitcount] = *enemy;
					hitcount++;
				}
				/*else
				{
				hitcount--;
				}
				}
				else
				{
				hitcount--;*/
			}

		}
		current = _Punch[spriteNr];
	}
	//Angriffstyp belegen
	attack.attackType = StandartAttack::Punch;
	//Anzahl hits der Struktur 
	attack.nrHits = hitcount;
	//Hits der Struktur hizufügen
	attack.hits = hits;
	//Schaden der Struktur hinzufügen
	attack.damage = 1;
	//SAFE_DELETE(hits);

}

void Character::Kick(SDL_Rect* mobs, SDL_Rect* enemy, int mobCount)
{
	//analog zu Punch()
	attack.hits = new SDL_Rect();
	hitcount = 0;

	SDL_Rect* hits = new SDL_Rect();
	kickFrameChange += dt;


	if (kickFrameChange > kickTimer)
	{
		spriteNr++;
		if (spriteNr > 7)
		{
			spriteNr = 0;
			kick = false;
		}
		kickFrameChange = 0;

		if (spriteNr == 5)
		{
			kickSound.Play(false);
			hits = collisionDetection(mobs, mobCount, false);
			//SAFE_DELETE(ahits);
			if (enemy != nullptr)
			{
				if (checkCollision(*enemy))
				{
					hits[hitcount] = *enemy;
					hitcount++;
				}
			}
		}
		current = _Kick[spriteNr];
	}
	attack.attackType = StandartAttack::Kick;
	attack.nrHits = hitcount;
	attack.hits = hits;
	attack.damage = 2;
	//SAFE_DELETE(hits);
}

void Character::Vanish()
{
	vanishFrameChange += dt;

	if (vanishFrameChange > 50)
	{
		vanishFrameChange = 0;
		if ((ultType == 1 || ultType == 2) && spriteNr == 2)
		{
			spriteNr++;
			isVanishing = false;
		}
		else
		{
			spriteNr++;
		}
		if (spriteNr < 7)
		{
			spriteNr += 1;

		}
		else
		{
			isVanishing = false;

		}
	}

	current = _Vanish[spriteNr];


}

void Character::Appear()
{
	vanishFrameChange += dt;

	if (vanishFrameChange > 50)
	{
		vanishFrameChange = 0;
		if (spriteNr < 7)
		{
			spriteNr += 1;

		}
		else
		{
			isAppearing = false;
		}
	}

	current = _Appear[spriteNr];
}

void Character::CalcLife(int damage)
{
	//Leben neu berechnen
	live -= damage;
}

void Character::CalcEnergy(int Energy)
{
	//Energie neu berechnen
	if (energy + Energy <= maxEnergy && energy + Energy >= 0)
	{
		energy += Energy;
	}
	else
	{
		if (energy + Energy >= maxEnergy)
		{
			energy = maxEnergy;

		}
		else
		{
			energy = 0;
		}
	}
}


SDL_Rect* Character::collisionDetection(SDL_Rect* rect, int rectCount, bool isPlatform)
{
	//SAFE_DELETE(ahits);
	ahits = new SDL_Rect();
	//Wenn rect nicht leer ist
	if (rect != nullptr)
	{
		//für die Anzahl an elemente
		for (int i = 0; i < rectCount; i++)
		{	//Wenn Kollision
			if (checkCollision(rect[i]))
			{
				//wenn es sich um ene Plattform handelts
				if (isPlatform)
				{
					if (currentPos.y + currentPos.h <= rect[i].y + 5)
					{
						//Character um gravitationswert zurücksetzen
						currentPos.y -= gravity;
						//Character ist nicht mehr in der Luft
						airborne = false;
						//spriteNr = 0;
					}
				}
				else //sonst
				{
					//hit dem Array hinzufügen
					ahits[hitcount] = rect[i];
					//count erhöhen
					hitcount++;
				}
			}
		}
	}

	return ahits;
}

bool Character::checkCollision(SDL_Rect rect)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = currentPos.x;
	rightA = currentPos.x + currentPos.w;
	topA = currentPos.y;
	bottomA = currentPos.y + currentPos.h;

	//Calculate the sides of rect B
	leftB = rect.x;
	rightB = rect.x + rect.w;
	topB = rect.y;
	bottomB = rect.y + rect.h;

	//If any of the sides from A are outside of B


	if (topA >= bottomB)
	{
		return false;

	}

	if (rightA <= leftB)
	{
		return false;

	}

	if (leftA >= rightB)
	{
		return false;

	}
	if (bottomA <= topB)
	{
		return false;

	}

	//If none of the sides from A are outside B
	return true;
}

void Character::AddGravity()
{
	if (airborne)
	{
		current = _Jump[4];
	}
	//Gravitation hinzufügen
	currentPos.y += gravity;
}

void Character::RenderSpecial()
{
	if (spAttck->IsActive())
	{
		spAttck->Render();
	}
}

void Character::RenderGUI()
{
	_hud.Render();
}



