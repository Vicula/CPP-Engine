// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: ProjectileEmitSystem.h
 * @brief: System used to emit projectiles from an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Events/KeyPressedEvent.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class ProjectileEmitSystem : public System
{
public:
    ProjectileEmitSystem()
    {
        RequireComponent<ProjectileEmitterComponent>();
        RequireComponent<TransformComponent>();
    };

    void SubscribeToEvents(std::unique_ptr<EventHandler> &eventHandler)
    {
        eventHandler->SubscribeToEvent<KeyPressedEvent>(this, &ProjectileEmitSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressedEvent &event)
    {
        if (event.inputHandler->isKeyDown(SDL_SCANCODE_SPACE))
        {
            for (auto entity : GetSystemEntities())
            {
                if (entity.HasComponent<CameraFollowComponent>())
                {
                    const auto projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
                    const auto transform = entity.GetComponent<TransformComponent>();
                    const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

                    // If parent entity has sprite, start the projectile position in the middle of the entity
                    glm::vec3 projectilePosition = transform.position;
                    if (entity.HasComponent<SpriteComponent>())
                    {
                        auto sprite = entity.GetComponent<SpriteComponent>();
                        projectilePosition.x += (transform.scale.x * sprite.width / 2);
                        projectilePosition.y += (transform.scale.y * sprite.height / 2);
                    }

                    // If parent entity direction is controlled by the keyboard keys, modify the direction of the projectile accordingly
                    glm::vec3 projectileVelocity = projectileEmitter.projectileVelocity;
                    int directionX = 0;
                    int directionY = 0;
                    if (rigidbody.velocity.x > 0)
                        directionX = +1;
                    if (rigidbody.velocity.x < 0)
                        directionX = -1;
                    if (rigidbody.velocity.y > 0)
                        directionY = +1;
                    if (rigidbody.velocity.y < 0)
                        directionY = -1;
                    projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
                    projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

                    // Create new projectile entity and add it to the world
                    entity.registry->CreateEntity()
                        .AddComponent<TransformComponent>(projectilePosition, glm::vec3(1.0, 1.0, 1.0), 0.0)
                        .AddComponent<RigidBodyComponent>(projectileVelocity)
                        .AddComponent<SpriteComponent>("bullet-image", 4, 4, 4)
                        .AddComponent<BoxColliderComponent>(4, 4)
                        .AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);
                }
            }
        }
    }

    void Update(std::unique_ptr<Registry> &registry)
    {
        for (auto entity : GetSystemEntities())
        {
            auto &projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
            const auto transform = entity.GetComponent<TransformComponent>();

            // If emission frequency is zero, bypass re-emission logic
            if (projectileEmitter.repeatFrequency == 0)
            {
                continue;
            }

            // Check if its time to re-emit a new projectile
            if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency)
            {
                glm::vec3 projectilePosition = transform.position;
                if (entity.HasComponent<SpriteComponent>())
                {
                    const auto sprite = entity.GetComponent<SpriteComponent>();
                    projectilePosition.x += (transform.scale.x * sprite.width / 2);
                    projectilePosition.y += (transform.scale.y * sprite.height / 2);
                }

                // Add a new projectile entity to the registry
                registry->CreateEntity()
                    .AddComponent<TransformComponent>(projectilePosition, glm::vec3(1.0, 1.0, 1.0), 0.0)
                    .AddComponent<RigidBodyComponent>(projectileEmitter.projectileVelocity)
                    .AddComponent<SpriteComponent>("bullet-image", 4, 4, 4)
                    .AddComponent<BoxColliderComponent>(4, 4)
                    .AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);

                // Update the projectile emitter component last emission to the current milliseconds
                projectileEmitter.lastEmissionTime = SDL_GetTicks();
            }
        }
    }
};

#endif /* __PROJECTILEEMITSYSTEM_H__ */