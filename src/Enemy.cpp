#include "Enemy.h"

#include <iostream>

Enemy::Enemy(glm::vec3 positionIn) : Entity(positionIn)
{
	pvMax = 10;
	pvCurrent = pvMax;

	attackMax = 7;
	attackCurrent = attackMax;

	defenceMax = 2;
	defenceCurrent = defenceMax;

	speedMax = 3; // will attack every 1 - (x/10)  = 0.7 s
	speedCurrent = speedMax;

	luckMax = 10;
	luckCurrent = luckMax;
}