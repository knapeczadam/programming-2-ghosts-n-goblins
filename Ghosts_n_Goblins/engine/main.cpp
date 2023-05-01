// Knapecz, Adam - 1DAE11

#include "pch.h"
#include <ctime>
#include "game/Game.h"

void StartHeapControl();
void DumpMemoryLeaks();

int SDL_main(int argv, char** args)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    StartHeapControl();

    // The size of the game window should be no larger than 1280 x 800.
    Game* pGame{new Game{Window{"Ghosts 'n Goblins - Knapecz, Adam - 1DAE11", 512.0f, 480.f}}}; // 448 + 32 (top margin)
    pGame->Run();
    delete pGame;

    DumpMemoryLeaks();
    return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
    // Notify user if heap is corrupt
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    // Report detected leaks when the program exits
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Set a breakpoint on the specified object allocation order number
     //_CrtSetBreakAlloc( 1931 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtDumpMemoryLeaks();
#endif
}
