#pragma once
#include "IEnemy.h"

class GreenMonster : public IEnemy
{
public:
    GreenMonster(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager);
    virtual ~GreenMonster() override = default;
    GreenMonster(const GreenMonster& other) = delete;
    GreenMonster(GreenMonster&& other) noexcept = delete;
    GreenMonster& operator=(const GreenMonster& other) = delete;
    GreenMonster& operator=(GreenMonster&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Wait() override;
    virtual void Shoot() override;
};
