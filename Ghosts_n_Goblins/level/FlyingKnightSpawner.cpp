#include "pch.h"
#include "FlyingKnightSpawner.h"

FlyingKnightSpawner::FlyingKnightSpawner(const Rectf& boundaries,
    GameController* pGameController)
        : ISpawner{boundaries, pGameController}
{
}

void FlyingKnightSpawner::Spawn()
{
}
