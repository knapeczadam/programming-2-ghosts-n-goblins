#pragma once
#include "IEnemy.h"
#include "IPotter.h"

/**
 * \brief 
 * Zombies are the first enemies that you will ever encounter.
 * They climb out of the graveyard soil, and march unerringly in your direction.
 * They only take one shot to destroy, and they are worth 200 points.
 * They are the bearers of pots, and you will only ever see three above ground at one time.
 * You will encounter them on Stage 3 in addition to the first stage.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Zombies">StrategyWiki</a>
 */
class Zombie final : public IEnemy, public IPotter
{
public:
    explicit Zombie(const Point2f& pos, GameController* pGameController);
    virtual ~Zombie() override = default;
    Zombie(const Zombie& other) = delete;
    Zombie(Zombie&& other) noexcept = delete;
    Zombie& operator=(const Zombie& other) = delete;
    Zombie& operator=(Zombie&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    virtual void Reset() override;

protected:
    virtual void Walk(float elapsedSec) override;
    virtual void Spawn(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;

private:
    void Sleep(float elapsedSec);

private:
    const float m_MinWalingTime;
    const float m_MaxWalingTime;
    float m_WalkingTime;
    const float m_SpawnTime;
    bool m_CanWalk;
    int m_Dir;
    const float m_MidColliderHeight;
};
