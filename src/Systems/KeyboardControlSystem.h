// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: KeyboardMovementSystem.h
 * @brief: System used to correlate movement to keypressed events
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../Handlers/EventHandler.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlSystem : public System
{
public:
    KeyboardControlSystem()
    {
        RequireComponent<KeyboardControlledComponent>();
        RequireComponent<SpriteComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToEvents(std::unique_ptr<EventHandler> &eventHandler)
    {
        eventHandler->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
    }

    void OnKeyPressed(KeyPressedEvent &event)
    {
        for (auto entity : GetSystemEntities())
        {
            const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
            auto &sprite = entity.GetComponent<SpriteComponent>();
            auto &rigidbody = entity.GetComponent<RigidBodyComponent>();

            if (event.inputHandler->isKeyDown(SDL_SCANCODE_UP) ||
                event.inputHandler->isKeyDown(SDL_SCANCODE_W))
            {
                rigidbody.velocity = keyboardcontrol.upVelocity;
                sprite.srcRect.y = sprite.height * 0;
            }
            if (event.inputHandler->isKeyDown(SDL_SCANCODE_RIGHT) ||
                event.inputHandler->isKeyDown(SDL_SCANCODE_D))
            {
                rigidbody.velocity = keyboardcontrol.rightVelocity;
                sprite.srcRect.y = sprite.height * 1;
            }
            if (event.inputHandler->isKeyDown(SDL_SCANCODE_DOWN) ||
                event.inputHandler->isKeyDown(SDL_SCANCODE_S))
            {
                rigidbody.velocity = keyboardcontrol.downVelocity;
                sprite.srcRect.y = sprite.height * 2;
            }
            if (event.inputHandler->isKeyDown(SDL_SCANCODE_LEFT) ||
                event.inputHandler->isKeyDown(SDL_SCANCODE_A))
            {
                rigidbody.velocity = keyboardcontrol.leftVelocity;
                sprite.srcRect.y = sprite.height * 3;
            }
        }
    }

    void Update()
    {
    }
};

#endif /* __KEYBOARDCONTROLSYSTEM_H__ */