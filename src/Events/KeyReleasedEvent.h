// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: KeyReleasedEvent.h
 * @brief: Event used to to represent a key release
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef KEYRELEASEDEVENT_H
#define KEYRELEASEDEVENT_H

#include <SDL2/SDL.h>

#include "Event.h"
#include "../Handlers/InputHandler.h"

class KeyReleasedEvent : public Event
{
public:
    InputHandler *inputHandler;
    KeyReleasedEvent(InputHandler &inputHandler) : inputHandler(&inputHandler) {}
};

#endif /* __KEYRELEASEDEVENT_H__ */