#pragma once
#include "ISpawner.h"

class ZombieSpawner final : public ISpawner
{
public:
    explicit  ZombieSpawner(const Rectf& boundaries,  GameController* pGameController);
    virtual ~ZombieSpawner() override = default;
    ZombieSpawner(const ZombieSpawner&) = delete;
    ZombieSpawner(ZombieSpawner&&) = delete;
    ZombieSpawner& operator=(const ZombieSpawner&) = delete;
    ZombieSpawner& operator=(ZombieSpawner&&) = delete;

    virtual void Spawn() override;
private:
    const float m_MinRange;
    const float m_MaxRange;
};
