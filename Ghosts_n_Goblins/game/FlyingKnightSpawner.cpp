#include "pch.h"
#include "FlyingKnightSpawner.h"

FlyingKnightSpawner::FlyingKnightSpawner(const Rectf& boundaries,
    GameController* pGameController)
        : Spawner{boundaries, pGameController}
{
}

void FlyingKnightSpawner::Spawn()
{
}
