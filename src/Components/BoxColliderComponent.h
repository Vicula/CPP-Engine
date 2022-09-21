// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   BoxColliderComponent.h
 * @brief:  Component used to add collision to an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

struct BoxColliderComponent
{
    int width;
    int height;
    glm::vec2 offset;

    BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0))
    {
        this->width = width;
        this->height = height;
        this->offset = offset;
    }
};

#endif /* __BOXCOLLIDERCOMPONENT_H__ */