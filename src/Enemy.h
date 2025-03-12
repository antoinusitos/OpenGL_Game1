#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:

public:
    Enemy(glm::vec3 positionIn);

public:
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

};

