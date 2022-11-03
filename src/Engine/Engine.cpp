#include <glad/glad.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

#include "Engine.h"
#include "../Logger/Logger.h"
#include "../Camera/Camera.h"
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
#include "../Models/Meshes/Texture.h"
#include "../Models/Shaders/Shader.h"
#include "../Models/Meshes/VAO.h"
#include "../Models/Meshes/VBO.h"
#include "../Models/Meshes/EBO.h"

#define WW 1000
#define WH (WW / 16) * 9
#define GL_GREY .07f, .13f, .17f, 1.0f

int Engine::windowWidth = WW;
int Engine::windowHeight = WH;
int Engine::mapWidth;
int Engine::mapHeight;
SDL_GLContext glcontext;

GLfloat vertices[] =
    {
        //     COORDINATES /   COLORS        /   TexCoord  //
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // Upper right corner
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
};

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

        // SDL_DisplayMode displayMode;
        // SDL_GetCurrentDisplayMode(0, &displayMode);
        // windowWidth = displayMode.w;
        // windowHeight = displayMode.h;

        // window = SDL_CreateWindow(
        //     NULL,
        //     SDL_WINDOWPOS_CENTERED,
        //     SDL_WINDOWPOS_CENTERED,
        //     windowWidth,
        //     windowHeight,
        //     SDL_WINDOW_BORDERLESS);
        // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

#pragma region setup Window
    window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        Logger::Err("Error creating SDL window.");
        return;
    };

    SDL_SetWindowSize(window, windowWidth, windowHeight);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(window, "Context 4.6 with GLAD");
    SDL_ShowWindow(window);
#pragma endregion setup Window

#pragma region setup GLContext
    // Create an OpenGL context for an OpenGL window, and make it current.
    glcontext = SDL_GL_CreateContext(window);

    if (!glcontext)
    {
        Logger::Err("Error creating OpenGL context.");
        return;
    };

    // Tell SDL/OpenGL what version it is
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // Load GLAD so it configures OpenGL
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = windowWidth, y = windowHeight
    glViewport(0, 0, windowWidth, windowHeight);
#pragma endregion setup GLContext

#pragma region setup Icon
    SDL_Surface *icon;
    icon = IMG_Load("./assets/images/tank-panther-right.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
#pragma endregion setup Icon

    // // Generates Shader object using shaders default.vert and default.frag
    // Shader shaderProgram("./src/Models/Shaders/vert/default.vert", "./src/Models/Shaders/frag/default.frag");

    // // Generates Vertex Array Object and binds it
    // VAO VAO1;
    // VAO1.Bind();

    // // Generates Vertex Buffer Object and links it to vertices
    // VBO VBO1(vertices, sizeof(vertices));
    // // Generates Element Buffer Object and links it to indices
    // EBO EBO1(indices, sizeof(indices));

    // // Links VBO attributes such as coordinates and colors to VAO
    // VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    // VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    // VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    // // Unbind all to prevent accidentally modifying them
    // VAO1.Unbind();
    // VBO1.Unbind();
    // EBO1.Unbind();

    // // Gets ID of uniform called "scale"
    // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // // Texture
    // Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    // brickTex.texUnit(shaderProgram, "tex0", 0);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

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
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                glViewport(0, 0, sdlEvent.window.data1, sdlEvent.window.data2);
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
                .AddComponent<TransformComponent>(glm::vec3(x * (tileScale * tileSize), y * (tileScale * tileSize), 0), glm::vec3(tileScale, tileScale, tileScale), 0.0)
                .AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
        }
    }
    mapFile.close();
    mapWidth = mapNumCols * tileSize * tileScale;
    mapHeight = mapNumRows * tileSize * tileScale;

    // Create an entity
    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec3(10.0, 100.0, 1), glm::vec3(1.0, 1.0 , 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
        .AddComponent<SpriteComponent>("chopper-image", 32, 32, 1)
        .AddComponent<AnimationComponent>(2, 15, true)
        .AddComponent<ProjectileEmitterComponent>(glm::vec3(150.0, 150.0, 1), 0, 10000, 0, true)
        .AddComponent<KeyboardControlledComponent>(glm::vec3(0, -100, 0), glm::vec3(100, 0, 0), glm::vec3(0, 100, 0), glm::vec3(-100, 0, 0))
        .AddComponent<CameraFollowComponent>()
        .AddComponent<HealthComponent>(100);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec3(windowWidth - 74, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
        .AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true)
        .AddComponent<AnimationComponent>(8, 5, true);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec3(500.0, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
        .AddComponent<SpriteComponent>("tank-image", 32, 32, 1)
        .AddComponent<BoxColliderComponent>(32, 32)
        .AddComponent<ProjectileEmitterComponent>(glm::vec3(100.0, 0.0, 0.0), 5000, 10000, 0, false)
        .AddComponent<HealthComponent>(100);

    registry->CreateEntity()
        .AddComponent<TransformComponent>(glm::vec3(10.0, 10.0, 1), glm::vec3(1.0, 1.0, 1.0), 0.0)
        .AddComponent<RigidBodyComponent>(glm::vec3(0.0, 0.0, 0.0))
        .AddComponent<SpriteComponent>("truck-image", 32, 32, 2)
        .AddComponent<BoxColliderComponent>(32, 32)
        .AddComponent<ProjectileEmitterComponent>(glm::vec3(0.0, 100.0 , 0.0), 2000, 10000, 0, false)
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
#pragma region renderer twoD
    // SDL_SetRenderDrawColor(renderer, 21, 21, 21, 1);
    // SDL_RenderClear(renderer);

    // registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);

    // isDebug && registry->GetSystem<RenderColliderSystem>().Update(renderer, camera);

    // SDL_RenderPresent(renderer);
#pragma endregion renderer twoD

    // Specify the color of the background
    glClearColor(GL_GREY);

    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

    // Swap the back buffer with the front buffer
    SDL_GL_SwapWindow(window);
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
    // Clean up shaders
    // shader won't actually be deleted by glDeleteShader until it's been detached.
    // glDetachShader(shading_program, vertexShader);
    // glDetachShader(shading_program, fragmentShader);
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);
    // glDeleteProgram(shading_program);
    assetStore->ClearAssets();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
};
