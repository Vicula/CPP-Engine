// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: CollisionSystem.h
 * @brief: System used to handle collision for an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL2/SDL.h>

class CollisionSystem : public System
{
public:
    CollisionSystem()
    {
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    };

    void Update()
    {
        auto entities = GetSystemEntities();

        for (auto i = entities.begin(); i != entities.end(); i++)
        {
            Entity a = *i;

            auto &collider = a.GetComponent<BoxColliderComponent>();
            auto &transform = a.GetComponent<TransformComponent>();

            for (auto j = i; j != entities.end(); j++)
            {
                Entity b = *j;

                if (a == b)
                    continue;

                auto &cmprCollider = b.GetComponent<BoxColliderComponent>();
                auto &cmprTransform = b.GetComponent<TransformComponent>();

                bool collisionHappened = CheckCollision(
                    transform.position.x + collider.offset.x,
                    transform.position.y + collider.offset.y,
                    collider.width,
                    collider.height,
                    cmprTransform.position.x + cmprCollider.offset.x,
                    cmprTransform.position.y + cmprCollider.offset.y,
                    cmprCollider.width,
                    cmprCollider.height);
                if (collisionHappened)
                {
                    a.Kill();
                    b.Kill();
                }
            }
        }
    }

    bool CheckCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
    {
        return (
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY);
    }
};

#endif /* __COLLISIONSYSTEM_H__ */