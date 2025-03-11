#include "PlayerManager.h"

#include <iostream>

PlayerManager::PlayerManager()
{
	pvMax = 99;
	pvCurrent = pvMax;

	attackMax = 7;
	attackCurrent = attackMax;

	defenceMax = 2;
	defenceCurrent = defenceMax;

	speedMax = 5; // will attack every 0.5 s
	speedCurrent = speedMax;

	luckMax = 10;
	luckCurrent = luckMax;
}