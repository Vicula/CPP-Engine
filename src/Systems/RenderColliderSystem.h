// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: RenderColliderSystem.h
 * @brief: Renders the collision box for debugging
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
#include <SDL2/SDL.h>

class RenderColliderSystem : public System
{
public:
    RenderColliderSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    };

    bool Update(SDL_Renderer *renderer, SDL_Rect &camera)
    {
        for (auto entity : GetSystemEntities())
        {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto collider = entity.GetComponent<BoxColliderComponent>();

            SDL_Rect colliderRect = {
                static_cast<int>(transform.position.x + collider.offset.x - camera.x),
                static_cast<int>(transform.position.y + collider.offset.y - camera.y),
                static_cast<int>(collider.width * transform.scale.x),
                static_cast<int>(collider.height * transform.scale.y)};

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
        return true;
    }
};

#endif /* __RENDERCOLLIDERSYSTEM_H__ */