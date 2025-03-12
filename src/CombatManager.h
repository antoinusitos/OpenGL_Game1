#pragma once

class Enemy;

class CombatManager
{
public:
    static CombatManager& GetInstance()
    {
        static CombatManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    CombatManager();

    void StartCombat(Enemy* enemy);

    void Tick(float deltaTime);

private:
    bool isInCombat = false;

    Enemy* currentEnemy = nullptr;
};

