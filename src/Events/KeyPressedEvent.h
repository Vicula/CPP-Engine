// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: KeyPressedEvent.h
 * @brief: Event used to to represent a key press
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../Handlers/Event.h"
#include "../Handlers/InputHandler.h"

class KeyPressedEvent : public Event
{
public:
    InputHandler *inputHandler;
    KeyPressedEvent(InputHandler &inputHandler) : inputHandler(&inputHandler) {}
};

#endif /* __KEYPRESSEDEVENT_H__ */