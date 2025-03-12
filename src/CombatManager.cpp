#include "CombatManager.h"

#include "Enemy.h"
#include "PlayerManager.h"
#include "TextRendererManager.h"
#include "WorldManager.h"

#include <iostream>

CombatManager::CombatManager()
{
}

void CombatManager::StartCombat(Enemy* enemy)
{
	isInCombat = true;
	currentEnemy = enemy;
}

void CombatManager::Tick(float deltaTime)
{
	if (!isInCombat)
	{
		return;
	}

	TextRendererManager::GetInstance().RenderText("IN COMBAT...", 1920.0f / 2.0f, 1080.0f / 2.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	PlayerManager::GetInstance().currentAttackDelay += deltaTime;
	if (PlayerManager::GetInstance().currentAttackDelay >= 1.0f - PlayerManager::GetInstance().speedCurrent / 10.0f)
	{
		std::cout << "player attack" << std::endl;
		currentEnemy->pvCurrent -= PlayerManager::GetInstance().attackCurrent;

		std::cout << "player pv:" << PlayerManager::GetInstance().pvCurrent << std::endl;
		std::cout << "enemy pv:" << currentEnemy->pvCurrent << std::endl;

		PlayerManager::GetInstance().currentAttackDelay = 0.0f;
		if (currentEnemy->pvCurrent <= 0)
		{
			isInCombat = false;
			WorldManager::GetInstance().RemoveEntity(currentEnemy);
			return;
		}
	}
	currentEnemy->currentAttackDelay += deltaTime;
	if (currentEnemy->currentAttackDelay >= 1.0f - currentEnemy->speedCurrent / 10.0f)
	{
		std::cout << "enemy attack" << std::endl;
		PlayerManager::GetInstance().pvCurrent -= currentEnemy->attackCurrent;

		std::cout << "player pv:" << PlayerManager::GetInstance().pvCurrent << std::endl;
		std::cout << "enemy pv:" << currentEnemy->pvCurrent << std::endl;

		currentEnemy->currentAttackDelay = 0.0f;
	}
}

const bool CombatManager::GetIsInCombat() const
{
	return isInCombat;
}