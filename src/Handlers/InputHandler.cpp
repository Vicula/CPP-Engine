#include "InputHandler.h"

#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Events/MouseMoveEvent.h"
#include "../Events/MouseButtonPressedEvent.h"
#include "../Events/MouseButtonReleasedEvent.h"

std::map<int, bool> InputHandler::_keys;

std::map<std::vector<int>, std::unique_ptr<std::list<std::unique_ptr<IInput>>>> InputHandler::_watchedInputs;

void InputHandler::ProcessInput(std::unique_ptr<EventHandler> &eventHandler)
{
    for (auto const &[key, input] : _watchedInputs)
    {
        if (getIsInputActive(key))
        {
            auto handlers = input.get();

            // if (handlers)
            // {
            //     for (auto it = handlers->begin(); it != handlers->end(); it++)
            //     {

            //     }
            // }
        }
    }
}

bool InputHandler::getIsInputActive(std::vector<int> keysToWatch) const
{
    bool result{true};

    for (int key : keysToWatch)
    {
        !_keys[key] && (result = false);
    }

    return result;
}

void InputHandler::SetupInput(std::shared_ptr<GLFWwindow> &_window)
{
    glfwSetKeyCallback(_window.get(), InputHandler::KeyCallback);
}

void InputHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::map<int, bool>::iterator it{_keys.find(key)};
    if (it != _keys.end())
        _keys[key] = action != GLFW_RELEASE;
}