#pragma once
#include "Spawner.h"

class ZombieSpawner : public Spawner
{
public:
    ZombieSpawner(const Rectf& boundaries,  GameController* pGameController);
    virtual ~ZombieSpawner() override = default;
    ZombieSpawner(const ZombieSpawner&) = delete;
    ZombieSpawner& operator=(const ZombieSpawner&) = delete;
    ZombieSpawner(ZombieSpawner&&) = delete;

    virtual void Spawn() override;
private:
    const int range;
};
