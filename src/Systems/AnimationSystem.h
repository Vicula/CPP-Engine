// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: AnimationSystem.h
 * @brief: System used to manipulate frames to animate an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
// #include <SDL2/SDL.h>

class AnimationSystem : public System
{
public:
    AnimationSystem()
    {
        RequireComponent<SpriteComponent>();
        RequireComponent<AnimationComponent>();
    };

    void Update()
    {
        for (auto entity : GetSystemEntities())
        {
            auto &animation = entity.GetComponent<AnimationComponent>();
            auto &sprite = entity.GetComponent<SpriteComponent>();

            // animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000) % animation.numFrames;
            // sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif /* __ANIMATIONSYSTEM_H__ */