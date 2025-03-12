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

    unsigned int pvMax = 0;
    unsigned int pvCurrent = 0;

    unsigned int attackMax = 0;
    unsigned int attackCurrent = 0;

    unsigned int defenceMax = 0;
    unsigned int defenceCurrent = 0;

    unsigned int speedMax = 0;
    unsigned int speedCurrent = 0;

    unsigned int luckMax = 0;
    unsigned int luckCurrent = 0;

};

