#pragma once
#include "IEnemy.h"

class Unicorn : public IEnemy
{
public:
    Unicorn(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager);
    virtual ~Unicorn() override = default;
    Unicorn(const Unicorn& other) = delete;
    Unicorn(Unicorn&& other) noexcept = delete;
    Unicorn& operator=(const Unicorn& other) = delete;
    Unicorn& operator=(Unicorn&& other) noexcept = delete;
    
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
