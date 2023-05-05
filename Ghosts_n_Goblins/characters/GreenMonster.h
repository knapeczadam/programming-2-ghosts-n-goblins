#pragma once
#include "IEnemy.h"

/*
 * The Green Monsters, also known as Eyeball Plants, are carnivorous plants whose favorite snack is knights in crunchy armor.
 * They are stationary and their tops are covered with eyeballs.
 * They have so many eyeballs to spare, that occasionally, they open their mouths and spit one at you.
 * They take only one shot to hit, and are worth 100 points, but watch out for the eyeball projectile that they shoot at you.
 */
class GreenMonster : public IEnemy
{
public:
    GreenMonster(const Point2f& pos, Player* pPlayer,std::vector<GameObject*>& enemies, SpriteFactory* pSpriteFactory, SoundManager* pSoundManager);
    virtual ~GreenMonster() override = default;
    GreenMonster(const GreenMonster& other) = delete;
    GreenMonster(GreenMonster&& other) noexcept = delete;
    GreenMonster& operator=(const GreenMonster& other) = delete;
    GreenMonster& operator=(GreenMonster&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Wait(float elapsedSec) override;
    virtual void Shoot(float elapsedSec) override;
private:
    std::vector<GameObject*>& m_EnemyThrowables;
};
