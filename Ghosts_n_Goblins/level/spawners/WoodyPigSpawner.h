#pragma once
#include "ISpawner.h"

class WoodyPigSpawner final : public ISpawner
{
public:
    explicit WoodyPigSpawner(const Rectf& boundaries, GameController* pGameController);
    virtual ~WoodyPigSpawner() override = default;
    WoodyPigSpawner(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner(WoodyPigSpawner&&) = delete;
    WoodyPigSpawner& operator=(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner& operator=(WoodyPigSpawner&&) = delete;

    virtual void Spawn() override;
};
