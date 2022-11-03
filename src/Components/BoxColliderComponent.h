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
    int depth;
    glm::vec3 offset;

    BoxColliderComponent(int width = 0, int height = 0, int depth = 0, glm::vec3 offset = glm::vec3(0))
    {
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->offset = offset;
    }
};

#endif /* __BOXCOLLIDERCOMPONENT_H__ */