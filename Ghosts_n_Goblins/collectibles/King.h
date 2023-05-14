#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

/**
 * \brief
 * This 10,000 point King doll is your reward for repeating the item emergence cycle a total of four times.
 * When the fourth cycle begins, this valuable doll can be collected.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Items">StrategyWiki</a>
 */
class King final : public GameObject, public ICollectible
{
public:
    explicit King(const Point2f& pos, GameController* pGameController);
    virtual ~King() override = default;
    King(const King& other) = delete;
    King(King&& other) noexcept = delete;
    King& operator=(const King& other) = delete;
    King& operator=(King&& other) noexcept = delete;
};
