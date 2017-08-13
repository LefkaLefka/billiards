#pragma once
#include "Cue.h"

public ref class Game
{
public: 
	// if gaming
	bool IsGame;
	bool IsProgress;
	Cue* Cue;
	bool IsCuePressed;
	CPoint* PointOnCue;

	Game()
	{
		IsGame = true;
		IsProgress = false;
		IsCuePressed = false;
	}
};