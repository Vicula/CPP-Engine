// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   ProjectileEmitterComponent.h
 * @brief:  Component used to give an enitity the ability to shoot projectiles
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct ProjectileEmitterComponent
{
    glm::vec3 projectileVelocity;
    int repeatFrequency;
    int projectileDuration;
    int hitPercentDamage;
    bool isFriendly;
    int lastEmissionTime;

    ProjectileEmitterComponent(glm::vec3 projectileVelocity = glm::vec3(0), int repeatFrequency = 0, int projectileDuration = 1000, int hitPercentDamage = 10, bool isFriendly = false)
    {
        this->projectileVelocity = projectileVelocity;
        this->repeatFrequency = repeatFrequency;
        this->projectileDuration = projectileDuration;
        this->hitPercentDamage = hitPercentDamage;
        this->isFriendly = isFriendly;
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif /* __PROJECTILEEMITTERCOMPONENT_H__ */