#include "./Engine/Engine.h"


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    
    Engine engine;

    engine.Init();
    engine.Run();
    engine.Destroy();

    return 0;
}
