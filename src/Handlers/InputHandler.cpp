#include "InputHandler.h"

#include "../Events/KeyPressedEvent.h"
#include "../Events/KeyReleasedEvent.h"
#include "../Events/MouseMoveEvent.h"
#include "../Events/MouseButtonPressedEvent.h"
#include "../Events/MouseButtonReleasedEvent.h"

InputHandler::InputHandler() : mousePosition(new glm::vec2(0, 0)), keystates(0)
{
    // reset all states
    for (int i = 0; i < 3; i++)
    {
        buttonStates.push_back(false);
    }
}

glm::vec2 *InputHandler::getMousePosition()
{
    return mousePosition;
}

void InputHandler::ProcessInput(std::unique_ptr<EventHandler> &eventHandler, bool *isRunning, bool *isDebug)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            *isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (sdlEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *isRunning = false;
                break;
            case SDLK_MINUS:
                *isDebug = !isDebug;
                break;
            }
            eventHandler->EmitEvent<KeyPressedEvent>(*this);
            onKeyDown();
            break;
        case SDL_KEYUP:
            eventHandler->EmitEvent<KeyReleasedEvent>(*this);
            onKeyUp();
            break;
        case SDL_MOUSEMOTION:
            eventHandler->EmitEvent<MouseMoveEvent>(*this);
            onMouseMove(sdlEvent);
            break;
        case SDL_MOUSEBUTTONDOWN:
            eventHandler->EmitEvent<MouseButtonPressedEvent>(*this);
            onMouseButtonDown(sdlEvent);
            break;
        case SDL_MOUSEBUTTONUP:
            eventHandler->EmitEvent<MouseButtonReleasedEvent>(*this);
            onMouseButtonUp(sdlEvent);
            break;
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                // TODO: make a resize window event and support it
                // glViewport(0, 0, sdlEvent.window.data1, sdlEvent.window.data2);
            }
            break;
        }
    };
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
    if (keystates != 0)
    {
        if (keystates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void InputHandler::onKeyDown()
{
    keystates = (Uint8 *)SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
    keystates = (Uint8 *)SDL_GetKeyboardState(0);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        buttonStates[SDL_BUTTON_LEFT - 1] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        buttonStates[SDL_BUTTON_MIDDLE - 1] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        buttonStates[SDL_BUTTON_RIGHT - 1] = true;
    }
}

void InputHandler::onMouseMove(SDL_Event &event)
{
    *mousePosition = glm::vec2(event.motion.x, event.motion.y);
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        buttonStates[SDL_BUTTON_LEFT - 1] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        buttonStates[SDL_BUTTON_MIDDLE - 1] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        buttonStates[SDL_BUTTON_RIGHT - 1] = false;
    }
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return buttonStates[buttonNumber];
}