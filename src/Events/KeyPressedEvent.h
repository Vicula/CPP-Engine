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

#include "../EventBus/Event.h"
#include "SDL2/SDL.h"

class KeyPressedEvent : public Event
{
public:
    SDL_Keycode symbol;
    KeyPressedEvent(SDL_Keycode symbol) : symbol(symbol) {}
};

#endif /* __KEYPRESSEDEVENT_H__ */