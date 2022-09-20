// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   RigidBodyComponent.h
 * @brief:  Component used to store physics data on an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent
{
    glm::vec2 velocity;
    glm::vec2 scale;
    double rotation;

    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0, 0))
    {
        this->velocity = velocity;
    };
};

#endif /* __RIGIDBODYCOMPONENT_H__ */