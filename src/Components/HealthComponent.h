// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   HealthComponent.h
 * @brief:  Component used to track health of an Entity
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <glm/glm.hpp>

struct HealthComponent
{
   int healthPercentage;

    HealthComponent(int healthPercentage = 0)
    {
        this->healthPercentage = healthPercentage;
    }
};

#endif /* __HEALTHCOMPONENT_H__ */