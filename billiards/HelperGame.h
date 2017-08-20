#pragma once
#include "Player.h"

class HelperGame
{
public:
	Player* Player1;
	Player* Player2;

	bool IsProgress;

	HelperGame()
	{
		Player1 = new Player();
		Player2 = new Player();
		IsProgress = false;
	}
};