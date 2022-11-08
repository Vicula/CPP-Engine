// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: ProjectileLifecycleSystem.h
 * @brief: System used to manipulate frames to animate an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileComponent.h"
// #include <SDL2/SDL.h>

class ProjectileLifecycleSystem : public System
{
public:
    ProjectileLifecycleSystem()
    {
        RequireComponent<ProjectileComponent>();
    };

    void Update()
    {
        for (auto entity : GetSystemEntities())
        {
            auto projectile = entity.GetComponent<ProjectileComponent>();

            // SDL_GetTicks() - projectile.startTime > projectile.duration && (entity.Kill());
        }
    }
};

#endif /* __PROJECTILELIFECYCLESYSTEM_H__ */