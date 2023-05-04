#pragma once
#include "IEnemy.h"

class Magician : public IEnemy
{
public:
    Magician(Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pFX, SoundManager* pSoundManager);
    virtual ~Magician() override = default;
    Magician(const Magician& other) = delete;
    Magician(Magician&& other) noexcept = delete;
    Magician& operator=(const Magician& other) = delete;
    Magician& operator=(Magician&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Shoot(float elapsedSec) override;
};
