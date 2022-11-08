// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: MouseButtonPressedEvent.h
 * @brief: Event used to to represent a mouse button press
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MOUSEBUTTONPRESSEDEVENT_H
#define MOUSEBUTTONPRESSEDEVENT_H

#include "../Handlers/Event.h"
#include "../Handlers/InputHandler.h"

class MouseButtonPressedEvent : public Event
{
public:
    InputHandler *inputHandler;
    MouseButtonPressedEvent(InputHandler &inputHandler) : inputHandler(&inputHandler) {}
};

#endif /* __MOUSEBUTTONPRESSEDEVENT_H__ */