// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: TransformComponent.h
 * @brief: Component used to store locational data on an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 scale;
    double rotation;

    TransformComponent(
        glm::vec3 position = glm::vec3(0, 0, 0),
        glm::vec3 scale = glm::vec3(1, 1, 1),
        double rotation = 0.0)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif /* __TRANSFORMCOMPONENT_H__ */