#pragma once
#include "IEnemy.h"

/**
 * \brief
 * The Red Arremer is possibly one of the most frustating enemies in Ghosts 'n Goblins, second only to the Satans.
 * They are found in every stage but the second stage and the final stage. They are intense guardians that rarely allow intruders past their posted position.
 * They begin on the ground, and leap into the air when fired upon.
 * They can spit balls of fire at you, and they like to maintain their aerial dominance as long as you are chucking weapons about.
 * After staying in the air for a while, they begin to swoop down on Arthur with deadly accuracy.
 * Only the fastest players will be able to outrun their dive. Red Arremers take three hits to destroy, and are worth 1000 points.
 * They may also be holding pots. Players rarely see the same Arremer for 60 seconds, as they usually destroy them, or get destroyed by them before that time.
 * However, if you do deal with the same Arremer for around 60 seconds, they turn white and become even more aggressive.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Red_Arremer">StrategyWiki</a>
 */
class RedArremer final : public IEnemy
{
private:
    enum class State
    {
        MEDITATING,
        WAKING_UP,
        WALKING,
        FLYING,
        FLYING_UP,
        FLYING_DOWN,
        FLYING_SIDEWAYS,
        WALKING_SHOOTING,
        FLYING_SHOOTING
    };

public:
    explicit RedArremer(const Point2f& pos, GameController* pGameController);
    virtual ~RedArremer() override = default;
    RedArremer(const RedArremer& other) = delete;
    RedArremer(RedArremer&& other) noexcept = delete;
    RedArremer& operator=(const RedArremer& other) = delete;
    RedArremer& operator=(RedArremer&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    virtual void LateUpdate(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;

protected:
    virtual void Walk(float elapsedSec) override;
    virtual void Shoot(float elapsedSec) override;
    virtual void Fly(float elapsedSec) override;


private:
    void UpdateState();
    void UpdateSprite();
    void RandomizeState();
private:
    State m_State;
    Point2f m_PosSnapshot;
    float m_AngleSnapshot;
    bool m_SnapshotTaken;
};
