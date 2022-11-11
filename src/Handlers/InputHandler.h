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

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include <list>

#include "../Logger/Logger.h"
#include "EventHandler.h"
#include "Input.h"

class InputHandler
{
private:
    // The GLFW callback for key events.  Sends events to all KeyInput instances
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    // Map from keyes to their pressed states
    static std::map<int, bool> _keys;
    // Keep a list of all KeyInput instances and notify them all of key events
    static std::map<std::vector<int>, std::unique_ptr<std::list<std::unique_ptr<IInput>>>> _watchedInputs;

    bool getIsInputActive(std::vector<int> keysToWatch) const;

public:
    InputHandler()
    {
        Logger::Log("InputHandler created");
    };

    ~InputHandler()
    {
        Logger::Log("InputHandler destroyed");
    };

    void ProcessInput(std::unique_ptr<EventHandler> &eventHandler);

    // Must be called before any Input instances will work
    static void SetupInput(std::shared_ptr<GLFWwindow> &_window);

    template <typename TEvent>
    void AddInput(std::vector<int> keysToMonitor)
    {
        if (!_watchedInputs[keysToMonitor].get())
        {
            _watchedInputs[keysToMonitor] = {std::make_unique<std::list<std::unique_ptr<IInput>>>()};

            for (int key : keysToMonitor)
            {
                std::map<int, bool>::iterator it{_keys.find(key)};
                if (it == _keys.end())
                    _keys[key] = {};
            }
        }
        auto input{std::make_unique<Input<TEvent>>(keysToMonitor)};
        _watchedInputs[keysToMonitor]->push_back(std::move(input));
    };
};

#endif /* __INPUTHANDLER_H__ */