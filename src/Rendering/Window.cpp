#include "Window.h"

#include <iostream>

#include "../Logger/Logger.h"

Window::Window(std::string title, int width, int height)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        Logger::Err("Error initialzing GLFW.");
        // Destroy();
        return;
    };

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of X by Y pixels
    _window = glfwCreateWindow(width, height, "OpenGL 4.6 Game", NULL, NULL);

    if (!_window)
    {
        Logger::Err("Error creating GLFW window.");
        // Destroy();
        return;
    };

    // TODO: Add Icon
    // SDL_Surface *icon;
    // icon = IMG_Load("./assets/images/tank-panther-right.png");
    // SDL_SetWindowIcon(window, icon);
    // SDL_FreeSurface(icon);

    // Introduce the window into the current context
    glfwMakeContextCurrent(_window);

    if (!gladLoadGL())
    {
        Logger::Err("Failed to init GLAD");
        // Destroy();
        return;
    }

    /// Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);
}

void Window::Update(){
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(_window);

    // Take care of all GLFW events
    glfwPollEvents();
};

void Window::Delete()
{
    // Delete window before ending the program
    glfwDestroyWindow(_window);

    // Terminate GLFW before ending the program
    glfwTerminate();
};
