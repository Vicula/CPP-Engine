// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   InputHandler.h
 * @brief:  Handler used to store all current states of the engines inputs
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <glm/glm.hpp>

#include "EventHandler.h"

class InputHandler
{
private:
    std::vector<bool> buttonStates;
    glm::vec2 *mousePosition;
    Uint8 *keystates;

public:
    InputHandler();
    ~InputHandler(){};
    void ProcessInput(std::unique_ptr<EventHandler> &eventHandler, bool *isRunning, bool *isDebug);

    /// Handling Mouse Event
    void onMouseButtonDown(SDL_Event &event);
    void onMouseMove(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);
    bool getMouseButtonState(int buttonNumber);
    glm::vec2 *getMousePosition();

    /// Handling Keyboard Event
    void onKeyDown();
    void onKeyUp();
    bool isKeyDown(SDL_Scancode key) const;
};

#endif /* __INPUTHANDLER_H__ */