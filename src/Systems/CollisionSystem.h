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
#include "../Handlers/EventHandler.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem : public System
{
public:
    CollisionSystem()
    {
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    };

    void Update(std::unique_ptr<EventHandler> &eventHandler)
    {
        auto entities = GetSystemEntities();

        // Loop all the entities that the system is interested in
        for (auto i = entities.begin(); i != entities.end(); i++)
        {
            Entity a = *i;

            auto &collider = a.GetComponent<BoxColliderComponent>();
            auto &transform = a.GetComponent<TransformComponent>();

            // Loop all the entities that still need to be checked (to the right of i)
            for (auto j = i; j != entities.end(); j++)
            {
                Entity b = *j;

                // Bypass if we are trying to test the same entity
                if (a == b)
                    continue;

                auto &cmprCollider = b.GetComponent<BoxColliderComponent>();
                auto &cmprTransform = b.GetComponent<TransformComponent>();

                // Perform the AABB collision check between entities a and b
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
                    Logger::Log("Entity " + std::to_string(a.GetId()) + " collided wih entity " + std::to_string(b.GetId()));
                    eventHandler->EmitEvent<CollisionEvent>(a, b);
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