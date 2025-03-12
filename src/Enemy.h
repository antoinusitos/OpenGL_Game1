#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:

public:
    Enemy(glm::vec3 positionIn);

public:
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

