// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   Engine.h
 * @brief:  Class that brings together all parts of the ECS system to
 *          generate a game
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ECS/ECS.h"
#include "../Rendering/Window.h"
// #include "../Stores/MeshStore.h"
// #include "../Camera/Camera.h"
// #include "../Stores/AssetStore.h"
// #include "../Stores/ShaderStore.h"

#include "../Handlers/EventHandler.h"

const int FPS = 120,
          MILLISECS_PER_FRAME = 1000 / FPS;

class Engine
{
private:
    bool isRunning{},
        isDebug{};
    int millisecsPreviousFrame{};
    std::unique_ptr<Window> window;
    // Camera camera;

    // std::unique_ptr<Registry> registry;
    // std::unique_ptr<MeshStore> meshStore;
    // std::unique_ptr<AssetStore> assetStore;
    // std::unique_ptr<ShaderStore> shaderStore;
    std::unique_ptr<EventHandler> eventHandler;

public:
    Engine();
    ~Engine();

    void Init(),
        Run(),
        Setup(),
        LoadLevel(int level),
        Update(),
        Render(),
        Destroy();

    static int windowWidth,
        windowHeight,
        mapWidth,
        mapHeight;
};

#endif /* __ENGINE_H__ */