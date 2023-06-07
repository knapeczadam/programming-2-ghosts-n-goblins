#pragma once
#include "IThrowable.h"
#include "collectibles/ICollectible.h"
#include "game/GameObject.h"

/**
 * \brief 
 * Torch (aka Flame):
 * The Torch can be very useful in some situations, and quite the opposite in others.
 * When thrown, it travels in an arc.
 * If and when it hits the ground (and not something else, such as a tombstone), it lights the ground on fire, creating a barrier that will kill most monsters that walk into it.
 * However, since you cannot throw more than two torches at a time, you may be forced to wait for the eruptions to end if both torches have hit the ground before you can throw another torch and defend yourself.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Weapons">StrategyWiki</a>
 */
class Torch final : public GameObject, public IThrowable, public ICollectible
{
public:
    Torch(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController);
    virtual ~Torch() override = default;
    Torch(const Torch& other) = delete;
    Torch(Torch&& other) noexcept = delete;
    Torch& operator=(const Torch& other) = delete;
    Torch& operator=(Torch&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;

private:
    bool m_Collectible;
};
