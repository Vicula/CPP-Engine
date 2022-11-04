// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: MouseMoveEvent.h
 * @brief: Event used to to represent when the mouse moves
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MOUSEMOVEEVENT_H
#define MOUSEMOVEEVENT_H

#include <SDL2/SDL.h>

#include "Event.h"
#include "../Handlers/InputHandler.h"

class MouseMoveEvent : public Event
{
public:
    InputHandler *inputHandler;
    MouseMoveEvent(InputHandler &inputHandler) : inputHandler(&inputHandler) {}
};

#endif /* __MOUSEMOVEEVENT_H__ */