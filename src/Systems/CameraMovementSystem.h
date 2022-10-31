// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: CameraMovementSystem.h
 * @brief: System used to manipulate locational data on an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraFollowComponent.h"
#include <SDL2/SDL.h>

class CameraMovementSystem : public System
{
public:
    CameraMovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<CameraFollowComponent>();
    };

    void Update(SDL_Rect &camera)
    {
        for (auto entity : GetSystemEntities())
        {
            auto &transform = entity.GetComponent<TransformComponent>();
            const auto &follow = entity.GetComponent<CameraFollowComponent>();

            camera.x = transform.position.x;
            camera.y = transform.position.y;
        }
    };
};

#endif /* __CAMERAMOVEMENTSYSTEM_H__ */