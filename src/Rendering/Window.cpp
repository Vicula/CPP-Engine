#include "Window.h"
#include "../Logger/Logger.h"

Window::Window(const std::string title, const int width, const int height)
// : _window(nullptr, glfwDestroyWindow)
{
    _title = title;
    _width = width;
    _height = height;
    _inputs = std::make_unique<InputHandler>();
    Logger::Log("Window created");
}

Window::~Window()
{
    Delete();
    Logger::Log("Window destroyed");
};

void Window::Init()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        Logger::Err("Error initialzing GLFW.");
        Delete();
        return;
    };

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of X by Y pixels
    // _window.reset(glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL));
    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

    if (!_window)
    {
        Logger::Err("Error creating GLFW window.");
        Delete();
        return;
    };

    // Introduce the window into the current context
    glfwMakeContextCurrent(_window);

    // TODO: Add Icon
    // SDL_Surface *icon;
    // icon = IMG_Load("./assets/images/tank-panther-right.png");
    // SDL_SetWindowIcon(window, icon);
    // SDL_FreeSurface(icon);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Err("Failed to init GLAD");
        Delete();
        return;
    }

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, _width, _height);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // setup input processing
    // _inputs->SetupInput(_window);
}

void Window::Render()
{
    // Specify the color of the background
    glClearColor(.07f, .13f, .17f, 1.0f);

    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update(std::unique_ptr<EventHandler> &eventHandler)
{
    // _inputs->ProcessInput(eventHandler);
}

bool Window::ShouldRun() const
{
    return !glfwWindowShouldClose(_window);
}

void Window::NextFrame()
{
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(_window);

    // Take care of all GLFW events
    glfwPollEvents();
}

void Window::Delete()
{
    // Delete window before ending the program
    glfwDestroyWindow(_window);

    // Terminate GLFW before ending the program
    glfwTerminate();
};
