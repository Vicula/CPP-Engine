// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: CameraMovementSystem.h
 * @brief: System used to manipulate locational data of the camera
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
#include "../Engine/Engine.h"
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

            transform.position.x + (camera.w / 2) < Engine::mapWidth && (camera.x = transform.position.x - (Engine::windowWidth / 2));
            transform.position.y + (camera.h / 2) < Engine::mapHeight && (camera.y = transform.position.y - (Engine::windowHeight / 2));

            // Keep camera rectangle view inside screen limits
            camera.x =
                camera.x < 0
                    ? 0
                : camera.x > camera.w
                    ? camera.w
                    : camera.x;
            camera.y =
                camera.y < 0
                    ? 0
                : camera.y > camera.h
                    ? camera.h
                    : camera.y;
        }
    };
};

#endif /* __CAMERAMOVEMENTSYSTEM_H__ */