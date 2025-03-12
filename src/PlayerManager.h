#pragma once

class PlayerManager
{
public:
    static PlayerManager& GetInstance()
    {
        static PlayerManager    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

public:
    PlayerManager();

    float currentAttackDelay = 0;

    int pvMax = 0;
    int pvCurrent = 0;

    int attackMax = 0;
    int attackCurrent = 0;

    int defenceMax = 0;
    int defenceCurrent = 0;

    int speedMax = 0;
    int speedCurrent = 0;

    int luckMax = 0;
    int luckCurrent = 0;

    void Tick(float deltaTime);
};

