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
// #include "../Stores/MeshStore.h"
// #include "../Camera/Camera.h"
// #include "../Stores/AssetStore.h"
// #include "../Stores/ShaderStore.h"

#include "../Handlers/EventHandler.h"
#include "../Handlers/InputHandler.h"


const int FPS = 120;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Engine
{
private:
    bool isDebug;
    bool isRunning;
    int millisecsPreviousFrame = 0;
    GLFWwindow *window;
    // Camera camera;

    // std::unique_ptr<Registry> registry;
    // std::unique_ptr<MeshStore> meshStore;
    // std::unique_ptr<AssetStore> assetStore;
    // std::unique_ptr<ShaderStore> shaderStore;
    std::unique_ptr<EventHandler> eventHandler;
    std::unique_ptr<InputHandler> inputHandler;

public:
    Engine();
    ~Engine();
    void Init();
    void Run();
    void Setup();
    void LoadLevel(int level);
    void Update();
    void Render();
    void Destroy();

    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;
};

#endif /* __ENGINE_H__ */