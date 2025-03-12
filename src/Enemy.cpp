#include "Enemy.h"

#include <iostream>

Enemy::Enemy(glm::vec3 positionIn) : Entity(positionIn)
{
	entityType = EntityType::ENEMY;

	pvMax = 10;
	pvCurrent = pvMax;

	attackMax = 7;
	attackCurrent = attackMax;

	defenceMax = 2;
	defenceCurrent = defenceMax;

	speedMax = 2.5f; // will attack every 2 s
	speedCurrent = speedMax;

	luckMax = 10;
	luckCurrent = luckMax;
}