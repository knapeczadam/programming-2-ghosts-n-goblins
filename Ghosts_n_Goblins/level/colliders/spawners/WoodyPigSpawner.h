#pragma once
#include "ISpawner.h"
#include "level/colliders/ICollider.h"

class WoodyPigSpawner final : public ISpawner
{
public:
    explicit WoodyPigSpawner(const Rectf& shape, GameController* pGameController);
    virtual ~WoodyPigSpawner() override = default;
    WoodyPigSpawner(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner(WoodyPigSpawner&&) = delete;
    WoodyPigSpawner& operator=(const WoodyPigSpawner&) = delete;
    WoodyPigSpawner& operator=(WoodyPigSpawner&&) = delete;

    virtual void Spawn() override;
private:
    const float m_MinRange;
    const float m_MaxRange;
};
