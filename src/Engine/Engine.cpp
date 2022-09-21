#include "Engine.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <fstream>

Engine::Engine()
{
    isRunning = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
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
    windowWidth = 1000; // displayMode.w
    windowHeight = 800; // displayMode.h

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
    };

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        Logger::Err("Error creating SDL renderer");
        return;
    };
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
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
            switch (sdlEvent.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_MINUS:
                debugMode = !debugMode;
                break;
            }
            break;
        }
    };
};

void Engine::LoadLevel(int level)
{
    // Add the sytems that need to be processed in our Engine
    registry
        ->AddSystem<MovementSystem>()
        ->AddSystem<RenderSystem>()
        ->AddSystem<AnimationSystem>()
        ->AddSystem<CollisionSystem>();

    // Adding assets to the asset store
    assetStore
        ->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png")
        ->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png")
        ->AddTexture(renderer, "chopper-image", "./assets/images/chopper.png")
        ->AddTexture(renderer, "radar-image", "./assets/images/radar.png")
        ->AddTexture(renderer, "tilemap-image", "./assets/tilemaps/jungle.png");

    int tileSize = 32;
    double tileScale = 2.0;
    int mapNumCols = 25;
    int mapNumRows = 20;
    std::fstream mapFile;
    mapFile.open("./assets/tilemaps/jungle.map");

    for (int y = 0; y < mapNumRows; y++)
    {
        for (int x = 0; x < mapNumCols; x++)
        {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;
            mapFile.ignore();

            registry
                ->CreateEntity()
                .AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0)
                .AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, srcRectX, srcRectY);
        }
    }
    mapFile.close();

    // Create an entity
    registry
        ->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("chopper-image", 32, 32, 1)
        .AddComponent<AnimationComponent>(2, 15);

    registry
        ->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("radar-image", 64, 64, 2)
        .AddComponent<AnimationComponent>(8, 5);

    registry
        ->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(30.0, 0.0))
        .AddComponent<SpriteComponent>("tank-image", 32, 32, 2)
        .AddComponent<BoxColliderComponent>(32, 32);

    registry
        ->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0))
        .AddComponent<SpriteComponent>("truck-image", 32, 32, 1)
        .AddComponent<BoxColliderComponent>(32, 32);
};

void Engine::Setup()
{
    LoadLevel(1);
};

void Engine::Update()
{
    // Can comment this out for uncapped FPS
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(MILLISECS_PER_FRAME);

    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    millisecsPreviousFrame = SDL_GetTicks();

    registry->Update();

    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update();
};

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 1);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

    SDL_RenderPresent(renderer);
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

void Engine::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};
