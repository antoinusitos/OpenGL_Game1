#include "PlayerManager.h"

#include "TextRendererManager.h"

#include <iostream>

PlayerManager::PlayerManager()
{
	pvMax = 99;
	pvCurrent = pvMax;

	attackMax = 7;
	attackCurrent = attackMax;

	defenceMax = 2;
	defenceCurrent = defenceMax;

	speedMax = 2; // will attack every 2 s
	speedCurrent = speedMax;

	luckMax = 10;
	luckCurrent = luckMax;
}

void PlayerManager::Tick(float deltaTime)
{
	std::string text = "HP: " + std::to_string(pvCurrent) + "/" + std::to_string(pvMax) + "   " + "ATT: " + std::to_string(attackCurrent);
	TextRendererManager::GetInstance().RenderText(text, 0.0f, 0.0f, 0.75f, glm::vec3(0.0f, 1.0f, 0.0f));
}