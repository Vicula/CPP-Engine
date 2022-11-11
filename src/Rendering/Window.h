// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   Window.h
 * @brief:  Window class used for creating an openGL context window
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../Handlers/InputHandler.h"
#include "../Handlers/EventHandler.h"

class Window
{
private:
    // std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> _window;
    GLFWwindow *_window;
    std::unique_ptr<InputHandler> _inputs;
    std::string _title;
    int _width,
        _height;

public:
    Window(const std::string title, const int width, const int height);
    ~Window();

    void Init(),
        Render(),
        Update(std::unique_ptr<EventHandler> &eventHandler),
        NextFrame(),
        Delete();
    bool ShouldRun() const;

    // template <typename TEvent>
    // void AddInput(std::vector<int> keysToMonitor)
    // {
    //     _inputs->AddInput<TEvent>(keysToMonitor);
    // };
};

#endif /* __WINDOW_CLASS_H__ */