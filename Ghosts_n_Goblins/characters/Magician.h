#pragma once
#include "IEnemy.h"

/**
 * \brief 
 * Tombstones line the ground of stage 1, and rocks occupy the floor of stage 3.
 * If Arthur fires 15 weapons upon either of these objects, a Magician will suddenly appear.
 * When he is solid, he unfurls his wings and sends a spell Arthur's way.
 * If Arthur is hit by this spell, he will be transformed into a Frog, and be defenseless for a number of seconds, before transforming back into a human.
 * He can be destroyed with one hit, and he is worth 2000 points, but it's best to avoid seeing him all together.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Magician">StrategyWiki</a>
*/
class Magician final : public IEnemy
{
public:
    explicit Magician(const Point2f& pos, GameController* pGameController);
    virtual ~Magician() override = default;
    Magician(const Magician& other) = delete;
    Magician(Magician&& other) noexcept = delete;
    Magician& operator=(const Magician& other) = delete;
    Magician& operator=(Magician&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    virtual void Reset() override;

protected:
    virtual void Shoot(float elapsedSec) override;

private:
    void Disappear();

private:
    bool m_CanShoot;
};
