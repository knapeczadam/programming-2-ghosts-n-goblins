#pragma once
#include "IEnemy.h"

class Crow :  public IEnemy
{
public:
    Crow(Sprite* pSprite, const Point2f& pos, Player* pPlayer,Sprite* pFX, SoundManager* pSoundManager);
    virtual ~Crow() override = default;
    Crow(const Crow& other) = delete;
    Crow(Crow&& other) noexcept = delete;
    Crow& operator=(const Crow& other) = delete;
    Crow& operator=(Crow&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Awake() override;
    virtual void Wait(float elapsedSec) override;
    virtual void Fly(float elapsedSec) override;

private:
    const float m_Amplitude;
};
