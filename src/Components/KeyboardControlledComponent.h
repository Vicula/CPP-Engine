// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   KeyboardControlledComponent.h
 * @brief:  Component used to add abilitiy to control an entity with
 *          keyboard inputs
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef KEYBOARDCONTROLLEDCOMPONENT_H
#define KEYBOARDCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct KeyboardControlledComponent
{
    glm::vec3 upVelocity;
    glm::vec3 rightVelocity;
    glm::vec3 downVelocity;
    glm::vec3 leftVelocity;

    KeyboardControlledComponent(glm::vec3 upVelocity = glm::vec3(0), glm::vec3 rightVelocity = glm::vec3(0), glm::vec3 downVelocity = glm::vec3(0), glm::vec3 leftVelocity = glm::vec3(0))
    {
        this->upVelocity = upVelocity;
        this->rightVelocity = rightVelocity;
        this->downVelocity = downVelocity;
        this->leftVelocity = leftVelocity;
    }
};

#endif
