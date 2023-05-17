#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

/**
 * \brief 
 * Keys appear as soon as you defeat the stage boss.
 * They fall from the sky and open the door to the next stage.
 * If you are not wearing armor when you collect the key, your armor will automatically be restored.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Items">StrategyWiki</a>
 */
class Key final : public GameObject, public ICollectible
{
public:
    explicit Key(const Point2f& pos, GameController* pGameController);
    virtual ~Key() override = default;
    Key(const Key& other) = delete;
    Key(Key&& other) noexcept = delete;
    Key& operator=(const Key& other) = delete;
    Key& operator=(Key&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;
    bool IsOnGround() const;

private:
    float m_Speed;
    bool m_OnGround;
};
