#pragma once
#include "Cue.h"
#include "Player.h"

class Game
{
public: 
	bool IsGame;
	bool IsProgress;
	Cue* Cue;
	bool IsCuePressed;
	CPoint* PointOnCue;
	float LengthForSpeed;

	bool SetWhiteBall;
	bool IsBlack;

	Player* Player1;
	Player* Player2;

	//Game() {};

	Game()
	{
		IsGame = true;
		IsProgress = false;
		IsCuePressed = false;
		Cue = nullptr;

		IsBlack = false;
		SetWhiteBall = false;

		Player1 = new Player();
		Player2 = new Player();
		Player1->BallsCount = 0;
		Player2->BallsCount = 0;
		Player1->IsProgress = true;
		Player2->IsProgress = false;
	}
};