// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: SpriteComponent.h
 * @brief: Component used to store locational data on an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

struct SpriteComponent
{
    std::string assetId;
    int width;
    int height;
    int zIndex;
    bool isFixed;
    // SDL_Rect srcRect;

    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int zIndex = 0, bool isFixed = false, int srcRectX = 0, int srcRectY = 0)
    {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->zIndex = zIndex;
        this->isFixed = isFixed;
        // this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif /* __SPRITECOMPONENT_H__ */