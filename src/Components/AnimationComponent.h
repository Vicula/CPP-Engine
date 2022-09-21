// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   AnimationComponent.h
 * @brief:  Component used to animate an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL2/SDL.h>

struct AnimationComponent
{
    int numFrames;
    int currentFrame;
    int frameRateSpeed;
    bool isLoop;
    int startTime;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true)
    {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameRateSpeed = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif /* __ANIMATIONCOMPONENT_H__ */