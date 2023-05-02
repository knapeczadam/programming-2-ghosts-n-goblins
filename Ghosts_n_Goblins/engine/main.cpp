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

    // Original dimensions: 256 x 224
    // Original aspect ratio: 8:7
    // New dimensions: 512 x 480 TODO: should be 512 x 448 (2x)
    // New aspect ratio: 16:15
    // Vertical stretch is 1.0714285714
    // 480 = 448 + 32 (top margin)
    Game* pGame{new Game{Window{"Ghosts 'n Goblins - Knapecz, Adam - 1DAE11", 512.0f, 480.f}}};
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