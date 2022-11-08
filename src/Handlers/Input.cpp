#include "Input.h"
#include <algorithm>

std::vector<Input *> Input::_instances;

Input::Input(std::vector<int> keysToMonitor) : _isEnabled(true)
{
    for (int key : keysToMonitor)
    {
        _keys[key] = false;
    }
    // Add this instance to the list of instances
    Input::_instances.push_back(this);
}

Input::~Input()
{
    // Remove this instance from the list of instances
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool Input::getIsKeyDown(int key)
{
    bool result = false;
    if (_isEnabled)
    {
        std::map<int, bool>::iterator it = _keys.find(key);
        if (it != _keys.end())
        {
            result = _keys[key];
        }
    }
    return result;
}

void Input::setIsKeyDown(int key, bool isDown)
{
    std::map<int, bool>::iterator it = _keys.find(key);
    if (it != _keys.end())
    {
        _keys[key] = isDown;
    }
}

void Input::setupInputs(Window &window)
{
    glfwSetKeyCallback(window.GetWindow(), Input::callback);
}

void Input::callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Send key event to all Input instances
    for (Input *Input : _instances)
    {
        Input->setIsKeyDown(key, action != GLFW_RELEASE);
    }
}