#pragma once
#include "IEnemy.h"

class BigMan : public IEnemy
{
public:
    BigMan(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager);
    virtual ~BigMan() override = default;
    BigMan(const BigMan& other) = delete;
    BigMan(BigMan&& other) noexcept = delete;
    BigMan& operator=(const BigMan& other) = delete;
    BigMan& operator=(BigMan&& other) noexcept = delete;
    
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Wait(float elapsedSec) override;
    virtual void Walk(float elapsedSec) override;
    virtual void Jump(float elapsedSec) override;
    virtual void Shoot(float elapsedSec) override;

private:
};
