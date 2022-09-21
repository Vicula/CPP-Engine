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

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>

const int FPS = 120;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Engine
{
private:
    bool debugMode = false;
    bool isRunning;
    int millisecsPreviousFrame = 0;
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;

public:
    Engine();
    ~Engine();
    void Init();
    void Run();
    void Setup();
    void LoadLevel(int level);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;
};

#endif /* __ENGINE_H__ */