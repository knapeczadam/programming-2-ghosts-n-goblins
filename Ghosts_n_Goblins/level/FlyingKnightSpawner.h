#pragma once
#include "Spawner.h"

class FlyingKnightSpawner : public Spawner
{
public:
    FlyingKnightSpawner(const Rectf& boundaries, GameController* pGameController);
    virtual ~FlyingKnightSpawner() override = default;
    FlyingKnightSpawner(const FlyingKnightSpawner&) = delete;
    FlyingKnightSpawner& operator=(const FlyingKnightSpawner&) = delete;
    FlyingKnightSpawner(FlyingKnightSpawner&&) = delete;
    FlyingKnightSpawner& operator=(FlyingKnightSpawner&&) = delete;

    virtual void Spawn() override;
};
