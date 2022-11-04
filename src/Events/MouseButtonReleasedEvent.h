// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: MouseButtonReleasedEvent.h
 * @brief: Event used to to represent a mouse click release
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MOUSE_BUTTON_RELEASED_EVENT_H
#define MOUSE_BUTTON_RELEASED_EVENT_H

#include <SDL2/SDL.h>

#include "Event.h"
#include "../Handlers/InputHandler.h"

class MouseButtonReleasedEvent : public Event
{
public:
    InputHandler *inputHandler;
    MouseButtonReleasedEvent(InputHandler &inputHandler) : inputHandler(&inputHandler) {}
};

#endif /* __MOUSE_BUTTON_RELEASED_EVENT_H__ */