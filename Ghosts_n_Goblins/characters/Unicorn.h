#pragma once
#include "IEnemy.h"

/**
 * \brief
 * One Unicorn guards the gate at the end of Stage 1, while two of them double as the final boss of Stage 2.
 * Also known as Cyclops, these brutes don't mess around.
 * They like to intimidate their opponents by jumping high into the air and crashing down on the ground.
 * They can even leap directly over Arthur's head to quickly appear on his other side.
 * They can spit fireballs at Arthur as well, all though they tend not to do this too frequently.
 * When the moment strikes them, they like the charge across the ground, and attack that is particularly difficult to avoid.
 * You will need to fire 10 shots at them to destroy them, and they like to leap into the air when you are throwing weapons at them, so you should leap into the air as well in order to hit them.
 * If you take one down, they are worth 2000, and they might even be carrying a pot with them.
 * Unicorns occupy some parts of Stage 6 as well, but not as bosses.
 * In the Famicom/NES-based versions of the game, Unicorns are invulnerable to the Shield/Cross.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Unicorn">StrategyWiki</a>
 */
class Unicorn final : public IEnemy
{
private:
    enum class State
    {
        WAIT,
        WALK,
        JUMP,
        SHOOT
    };
public:
    explicit Unicorn(const Point2f& pos, GameController* pGameController);
    virtual ~Unicorn() override = default;
    Unicorn(const Unicorn& other) = delete;
    Unicorn(Unicorn&& other) noexcept = delete;
    Unicorn& operator=(const Unicorn& other) = delete;
    Unicorn& operator=(Unicorn&& other) noexcept = delete;
    
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    virtual void Awake(float elapsedSec) override;

protected:
    virtual void Wait(float elapsedSec) override;
    virtual void Walk(float elapsedSec) override;
    virtual void Jump(float elapsedSec) override;
    virtual void Shoot(float elapsedSec) override;

private:
};
