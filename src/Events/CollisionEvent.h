// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: CollisionEvent.h
 * @brief: Event used to to represent a collision of two or more entites
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent : public Event
{
public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b) : a(a), b(b){};
};

#endif /* __COLLISIONEVENT_H__ */