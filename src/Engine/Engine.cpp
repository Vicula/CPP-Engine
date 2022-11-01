#include "Engine.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/ProjectileLifecycleSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <fstream>

int Engine::windowWidth;
int Engine::windowHeight;
int Engine::mapWidth;
int Engine::mapHeight;

Engine::Engine()
{
    isRunning = false;
    isDebug = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();
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

    // Initalize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = windowWidth;
    camera.h = windowHeight;

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
                isDebug = !isDebug;
                break;
            }
            eventBus->EmitEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
            break;
        }
    };
};

void Engine::LoadLevel(int level)
{
    // Add the sytems that need to be processed in our Engine
    registry
        ->AddSystem<MovementSystem>()
        ->AddSystem<CameraMovementSystem>()
        ->AddSystem<RenderSystem>()
        ->AddSystem<AnimationSystem>()
        ->AddSystem<CollisionSystem>()
        ->AddSystem<RenderColliderSystem>()
        ->AddSystem<DamageSystem>()
        ->AddSystem<ProjectileEmitSystem>()
        ->AddSystem<KeyboardControlSystem>()
        ->AddSystem<ProjectileLifecycleSystem>();

    // Adding assets to the asset store
    assetStore
        ->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png")
        ->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png")
        ->AddTexture(renderer, "chopper-image", "./assets/images/chopper-spritesheet.png")
        ->AddTexture(renderer, "radar-image", "./assets/images/radar.png")
        ->AddTexture(renderer, "bullet-image", "./assets/images/bullet.png")
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
                .AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
        }
    }
    mapFile.close();
    mapWidth = mapNumCols * tileSize * tileScale;
    mapHeight = mapNumRows * tileSize * tileScale;

    // Create an entity
    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(10.0, 100.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("chopper-image", 32, 32, 1)
        .AddComponent<AnimationComponent>(2, 15, true)
        .AddComponent<ProjectileEmitterComponent>(glm::vec2(150.0, 150.0), 0, 10000, 0, true)
        .AddComponent<KeyboardControlledComponent>(glm::vec2(0, -100), glm::vec2(100, 0), glm::vec2(0, 100), glm::vec2(-100, 0))
        .AddComponent<CameraFollowComponent>()
        .AddComponent<HealthComponent>(100);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true)
        .AddComponent<AnimationComponent>(8, 5, true);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(500.0, 10.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("tank-image", 32, 32, 1)
        .AddComponent<BoxColliderComponent>(32, 32)
        .AddComponent<ProjectileEmitterComponent>(glm::vec2(100.0, 0.0), 5000, 10000, 0, false)
        .AddComponent<HealthComponent>(100);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0))
        .AddComponent<SpriteComponent>("truck-image", 32, 32, 2)
        .AddComponent<BoxColliderComponent>(32, 32)
        .AddComponent<ProjectileEmitterComponent>(glm::vec2(0.0, 100.0), 2000, 10000, 0, false)
        .AddComponent<HealthComponent>(100);
};

void Engine::Setup()
{
    LoadLevel(1);
};

void Engine::Update()
{
    // If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
    // Can comment this out for uncapped FPS
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
        SDL_Delay(MILLISECS_PER_FRAME);

    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    // Store the "previous" frame time
    millisecsPreviousFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventBus->Reset();

    // Perform the subscription of the events for all systems
    registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventBus);

    // Update the registry to process the entities that are waiting to be created/deleted
    registry->Update();

    // Invoke all the systems that need to update
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventBus);
    registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    registry->GetSystem<ProjectileLifecycleSystem>().Update();
    registry->GetSystem<CameraMovementSystem>().Update(camera);
};

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 1);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);

    isDebug && registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);

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
