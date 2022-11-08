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

class Window
{
private:
    GLFWwindow *_window;
    int _width;
    int _height;
    std::string _title;

public:
    Window(std::string title, int width, int height);
    ~Window();

    void Update();
    void Delete();
    GLFWwindow *GetWindow() const { return _window; }
};

#endif /* __WINDOW_CLASS_H__ */