// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   RenderSystem.h
 * @brief:  System used to render the sprite data of an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Stores/AssetStore.h"
#include <SDL2/SDL.h>

class RenderSystem : public System
{
public:
    RenderSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    };

    void Update(SDL_Renderer *renderer, std::unique_ptr<AssetStore> &assetStore, SDL_Rect &camera)
    {
        struct RenderableEntity
        {
            TransformComponent transformComponent;
            SpriteComponent spriteComponent;
        };
        std::vector<RenderableEntity> renderableEntities;
        for (auto entity : GetSystemEntities())
        {
            RenderableEntity renderableEntity;
            renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
            renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
            renderableEntities.emplace_back(renderableEntity);
        }

        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity &a, const RenderableEntity &b)
                  { return a.spriteComponent.zIndex < b.spriteComponent.zIndex; });

        for (auto entity : renderableEntities)
        {
            const auto transform = entity.transformComponent;
            const auto sprite = entity.spriteComponent;

            SDL_Rect srcRect = sprite.srcRect;

            SDL_Rect destRect = {
                static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),
                static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)};

            SDL_RenderCopyEx(
                renderer,
                assetStore->GetTexture(sprite.assetId),
                &srcRect,
                &destRect,
                transform.rotation,
                NULL,
                SDL_FLIP_NONE);
        };
    };
};

#endif /* __RENDERSYSTEM_H__ */