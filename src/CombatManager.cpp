#include "CombatManager.h"

#include "Enemy.h"
#include "PlayerManager.h"

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

	PlayerManager::GetInstance().currentAttackDelay += deltaTime;
	if (PlayerManager::GetInstance().currentAttackDelay >= 1.0f - PlayerManager::GetInstance().speedCurrent / 10.0f)
	{
		std::cout << "player attack" << std::endl;
		currentEnemy->pvCurrent -= PlayerManager::GetInstance().attackCurrent;

		std::cout << "player pv:" << PlayerManager::GetInstance().pvCurrent << std::endl;
		std::cout << "enemy pv:" << currentEnemy->pvCurrent << std::endl;

		PlayerManager::GetInstance().currentAttackDelay = 0.0f;
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