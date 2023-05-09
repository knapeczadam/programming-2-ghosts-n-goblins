#pragma once
#include "Spawner.h"

class WoodyPigSpawner : public Spawner
{
public:
    WoodyPigSpawner(const Rectf& boundaries, GameController* pGameController);
    virtual ~WoodyPigSpawner() override = default;
    WoodyPigSpawner(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner& operator=(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner(WoodyPigSpawner&&) = delete;

    virtual void Spawn() override;
};
