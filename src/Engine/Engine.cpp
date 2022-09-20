#include "Engine.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

Engine::Engine()
{
    isRunning = false;
    registry = std::make_unique<Registry>();
    Logger::Log("Created");
}

Engine::~Engine()
{
    Logger::Log("destoryed");
}

void Engine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error initialzing SDL.");
        return;
    };

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800;  // displayMode.w
    windowHeight = 600; // displayMode.h

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        Logger::Err("Error creating SDL window.");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        Logger::Err("Error creating SDL renderer");
        return;
    }
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
};

void Engine::Setup()
{
    Entity tank = registry->CreateEntity();
    registry->AddComponent<TransformComponent>(tank, glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(tank, glm::vec2(50.0, 0.0));

    Entity tank2 = registry->CreateEntity();
    registry->AddComponent<TransformComponent>(tank2, glm::vec2(50.0, 50.0), glm::vec2(1.0, 1.0), 0.0);
    registry->AddComponent<RigidBodyComponent>(tank2, glm::vec2(50.0, 0.0));
}

void Engine::Update()
{
    // Can comment this out for uncapped FPS
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(MILLISECS_PER_FRAME);

    // double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    millisecsPreviousFrame = SDL_GetTicks();
};

void Engine::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            break;
        }
    };
};

void Engine::Run()
{
    Setup();

    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
};

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 1);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
};

void Engine::Destory()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};