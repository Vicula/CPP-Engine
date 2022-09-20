// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: MovementSystem.h
 * @brief: System used to manipulate locational data on an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <../ECS/ECS.h>
#include <glm/glm.hpp>

class MovementSystem : public System
{
public:
    MovementSystem() {}
    void Update() {}
};

#endif /* __MOVEMENTSYSTEM_H__ */