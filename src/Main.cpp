#include "./Engine/Engine.h"


int main(int argc, char* argv[])
{
   Engine engine;

   engine.Init();
   engine.Run();
   engine.Destory();

    return 0;
}
