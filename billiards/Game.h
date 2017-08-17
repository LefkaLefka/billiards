#pragma once
#include "Cue.h"

public ref class Game
{
public: 
	bool IsGame;
	bool IsProgress;
	Cue* Cue;
	bool IsCuePressed;
	CPoint* PointOnCue;
	float LengthForSpeed;

	Game()
	{
		IsGame = true;
		IsProgress = false;
		IsCuePressed = false;
	}
};