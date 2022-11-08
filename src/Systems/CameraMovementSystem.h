// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: CameraMovementSystem.h
 * @brief: System used to manipulate locational data of the camera
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Engine/Engine.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraFollowComponent.h"
// #include <SDL2/SDL.h>

class CameraMovementSystem : public System
{
public:
    CameraMovementSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<CameraFollowComponent>();
    };

    // void Update(SDL_Rect &camera)
    // {
        // for (auto entity : GetSystemEntities())
        // {
            // auto &transform = entity.GetComponent<TransformComponent>();

            // transform.position.x + (camera.w / 2) < Engine::mapWidth && (camera.x = transform.position.x - (Engine::windowWidth / 2));
            // transform.position.y + (camera.h / 2) < Engine::mapHeight && (camera.y = transform.position.y - (Engine::windowHeight / 2));

            // // Keep camera rectangle view inside screen limits
            // camera.x =
            //     camera.x < 0
            //         ? 0
            //     : camera.x > camera.w
            //         ? camera.w
            //         : camera.x;
            // camera.y =
            //     camera.y < 0
            //         ? 0
            //     : camera.y > camera.h
            //         ? camera.h
            //         : camera.y;
    //     }
    // };
};

// // Handles key inputs
// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// {
//     Position += speed * Orientation;
// }
// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// {
//     Position += speed * -glm::normalize(glm::cross(Orientation, Up));
// }
// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// {
//     Position += speed * -Orientation;
// }
// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// {
//     Position += speed * glm::normalize(glm::cross(Orientation, Up));
// }
// if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
// {
//     Position += speed * Up;
// }
// if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
// {
//     Position += speed * -Up;
// }
// if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
// {
//     speed = 0.4f;
// }
// else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
// {
//     speed = 0.1f;
// }

// // Handles mouse inputs
// if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
// {
//     // Hides mouse cursor
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

//     // Prevents camera from jumping on the first click
//     if (firstClick)
//     {
//         glfwSetCursorPos(window, (width / 2), (height / 2));
//         firstClick = false;
//     }

//     // Stores the coordinates of the cursor
//     double mouseX;
//     double mouseY;
//     // Fetches the coordinates of the cursor
//     glfwGetCursorPos(window, &mouseX, &mouseY);

//     // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
//     // and then "transforms" them into degrees
//     float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
//     float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

//     // Calculates upcoming vertical change in the Orientation
//     glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

//     // Decides whether or not the next vertical Orientation is legal or not
//     if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
//     {
//         Orientation = newOrientation;
//     }

//     // Rotates the Orientation left and right
//     Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

//     // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
//     glfwSetCursorPos(window, (width / 2), (height / 2));
// }
// else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
// {
//     // Unhides cursor since camera is not looking around anymore
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//     // Makes sure the next time the camera looks around it doesn't jump
//     firstClick = true;
// }

#endif /* __CAMERAMOVEMENTSYSTEM_H__ */