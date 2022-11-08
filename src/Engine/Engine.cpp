#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

// Core
#include "Engine.h"
#include "../Logger/Logger.h"

// Events
// #include "../Events/KeyReleasedEvent.h"
// #include "../Events/MouseMoveEvent.h"
// #include "../Events/MouseButtonPressedEvent.h"
// #include "../Events/MouseButtonReleasedEvent.h"

// Components
// #include "../Components/TransformComponent.h"
// #include "../Components/RigidBodyComponent.h"
// #include "../Components/SpriteComponent.h"
// #include "../Components/MeshComponent.h"
// #include "../Components/AnimationComponent.h"
// #include "../Components/BoxColliderComponent.h"
// #include "../Components/KeyboardControlledComponent.h"
// #include "../Components/CameraFollowComponent.h"
// #include "../Components/ProjectileEmitterComponent.h"
// #include "../Components/HealthComponent.h"

// Systems
// #include "../Systems/MovementSystem.h"
// #include "../Systems/CameraMovementSystem.h"
// #include "../Systems/RenderSystem.h"
// #include "../Systems/AnimationSystem.h"
// #include "../Systems/CollisionSystem.h"
// #include "../Systems/RenderColliderSystem.h"
// #include "../Systems/DamageSystem.h"
// #include "../Systems/ProjectileEmitSystem.h"
// #include "../Systems/KeyboardControlSystem.h"
// #include "../Systems/ProjectileLifecycleSystem.h"

#define WW 1000
#define WH (WW / 16) * 9
#define GL_GREY .07f, .13f, .17f, 1.0f

int Engine::windowWidth = WW;
int Engine::windowHeight = WH;
int Engine::mapWidth;
int Engine::mapHeight;

// Vertices coordinates
GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};

// Indices for vertices order
GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1  // Upper triangle
};

Engine::Engine()
{
    isRunning = false;
    isDebug = false;
    // registry = std::make_unique<Registry>();
    // meshStore = std::make_unique<MeshStore>();
    // assetStore = std::make_unique<AssetStore>();
    // shaderStore = std::make_unique<ShaderStore>();
    eventHandler = std::make_unique<EventHandler>();
    inputHandler = std::make_unique<InputHandler>();
    // Creates camera object
    // camera = Camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));
    Logger::Log("Engine Created");
}

Engine::~Engine()
{
    Logger::Log("Engine Destoryed");
}

void Engine::Init()
{


};

void Engine::LoadLevel(int level){
    // Add the sytems that need to be processed in our Engine
    // registry
    //     ->AddSystem<MovementSystem>()
    //     ->AddSystem<CameraMovementSystem>()
    //     ->AddSystem<RenderSystem>()
    //     ->AddSystem<AnimationSystem>()
    //     ->AddSystem<CollisionSystem>()
    //     ->AddSystem<RenderColliderSystem>()
    //     ->AddSystem<DamageSystem>()
    //     ->AddSystem<ProjectileEmitSystem>()
    //     ->AddSystem<KeyboardControlSystem>()
    //     ->AddSystem<ProjectileLifecycleSystem>();

    // Adding assets to the asset store
    // assetStore
    //     ->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
    //     ->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png")
    //     ->AddTexture(renderer, "chopper-image", "./assets/images/chopper-spritesheet.png")
    //     ->AddTexture(renderer, "radar-image", "./assets/images/radar.png")
    //     ->AddTexture(renderer, "bullet-image", "./assets/images/bullet.png")
    //     ->AddTexture(renderer, "tilemap-image", "./assets/tilemaps/jungle.png");

    // Create and Add shaders to the shader store
    // shaderStore->AddShader("default", "default.vs", "default.fs");

    // // Create and add Meshes to the mesh store
    // meshStore->AddMesh(
    //     "default",
    //     *vertices,
    //     *indices);

    // registry->CreateEntity()
    //     .AddComponent<MeshComponent>("default", "default");

    // int tileSize = 32;
    // double tileScale = 2.0;
    // int mapNumCols = 25;
    // int mapNumRows = 20;
    // std::fstream mapFile;
    // mapFile.open("./assets/tilemaps/jungle.map");

    // for (int y = 0; y < mapNumRows; y++)
    // {
    //     for (int x = 0; x < mapNumCols; x++)
    //     {
    //         char ch;
    //         mapFile.get(ch);
    //         int srcRectY = std::atoi(&ch) * tileSize;
    //         mapFile.get(ch);
    //         int srcRectX = std::atoi(&ch) * tileSize;
    //         mapFile.ignore();

    //         // registry
    //         //     ->CreateEntity()
    //         //     .AddComponent<TransformComponent>(glm::vec3(x * (tileScale * tileSize), y * (tileScale * tileSize), 0), glm::vec3(tileScale, tileScale, tileScale), 0.0)
    //         //     .AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
    //     }
    // }
    // mapFile.close();
    // mapWidth = mapNumCols * tileSize * tileScale;
    // mapHeight = mapNumRows * tileSize * tileScale;

    // Create an entity
    // registry->CreateEntity()
    //     .AddComponent<TransformComponent>(glm::vec3(10.0, 100.0, 1), glm::vec3(1.0, 1.0 , 1.0), 0.0)
    //     .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
    //     .AddComponent<SpriteComponent>("chopper-image", 32, 32, 1)
    //     .AddComponent<AnimationComponent>(2, 15, true)
    //     .AddComponent<ProjectileEmitterComponent>(glm::vec3(150.0, 150.0, 1), 0, 10000, 0, true)
    //     .AddComponent<KeyboardControlledComponent>(glm::vec3(0, -100, 0), glm::vec3(100, 0, 0), glm::vec3(0, 100, 0), glm::vec3(-100, 0, 0))
    //     .AddComponent<CameraFollowComponent>()
    //     .AddComponent<HealthComponent>(100);

    // registry->CreateEntity()
    //     .AddComponent<TransformComponent>(glm::vec3(windowWidth - 74, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
    //     .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
    //     .AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true)
    //     .AddComponent<AnimationComponent>(8, 5, true);

    // registry->CreateEntity()
    //     .AddComponent<TransformComponent>(glm::vec3(500.0, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
    //     .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
    //     .AddComponent<SpriteComponent>("tank-image", 32, 32, 1)
    //     .AddComponent<BoxColliderComponent>(32, 32)
    //     .AddComponent<ProjectileEmitterComponent>(glm::vec3(100.0, 0.0, 0.0), 5000, 10000, 0, false)
    //     .AddComponent<HealthComponent>(100);

    // registry->CreateEntity()
    //     .AddComponent<TransformComponent>(glm::vec3(10.0, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
    //     .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
    //     .AddComponent<SpriteComponent>("truck-image", 32, 32, 2)
    //     .AddComponent<BoxColliderComponent>(32, 32)
    //     .AddComponent<ProjectileEmitterComponent>(glm::vec3(0.0, 100.0 , 0.0), 2000, 10000, 0, false)
    //     .AddComponent<HealthComponent>(100);
};

void Engine::Setup()
{
    // Init and setup current level
    LoadLevel(1);

    // Enables the Depth Buffer
    // glEnable(GL_DEPTH_TEST);

    // set Engine running to true
    isRunning = true;
};

void Engine::Update()
{
    // If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
    // Can comment this out for uncapped FPS
    // int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    // if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    //     SDL_Delay(MILLISECS_PER_FRAME);

    // // The difference in ticks since the last frame, converted to seconds
    // double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

    // // Store the "previous" frame time
    // millisecsPreviousFrame = SDL_GetTicks();

    // Reset all event handlers for the current frame
    eventHandler->Reset();

    // Perform the subscription of the events for all systems
    // registry->GetSystem<DamageSystem>().SubscribeToEvents(eventHandler);
    // registry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(eventHandler);
    // registry->GetSystem<ProjectileEmitSystem>().SubscribeToEvents(eventHandler);

    // Update the registry to process the entities that are waiting to be created/deleted
    // registry->Update();

    // Invoke all the systems that need to update
    // registry->GetSystem<MovementSystem>().Update(deltaTime);
    // registry->GetSystem<AnimationSystem>().Update();
    // registry->GetSystem<CollisionSystem>().Update(eventHandler);
    // registry->GetSystem<ProjectileEmitSystem>().Update(registry);
    // registry->GetSystem<ProjectileLifecycleSystem>().Update();
    // registry->GetSystem<CameraMovementSystem>().Update(camera);

    // TODO: Move into its own system
    // Updates and exports the camera matrix to the Vertex Shader
    // camera.updateMatrix(45.0f, 0.1f, 100.0f);
};

void Engine::Render()
{
    // Specify the color of the background
    glClearColor(GL_GREY);

    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
};

void Engine::Run()
{
    Setup();
    while (isRunning)
    {
        inputHandler->ProcessInput(window , eventHandler, &isRunning, &isDebug);
        Update();
        Render();
    }
};

void Engine::Destroy()
{
    // shaderStore->ClearShaders();
    // meshStore->ClearMeshes();
    // assetStore->ClearAssets();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
};
