#pragma once
#include "game/GameObject.h"

class IEnemy : public GameObject
{
public:
    IEnemy(Game::Label label, Sprite* pSprite, const Point2f& pos, Player* pPlayer, Sprite* pPX, SoundManager* pSoundManager);
    virtual ~IEnemy() override = default;
    IEnemy(const IEnemy& other) = delete;
    IEnemy(IEnemy&& other) noexcept = delete;
    IEnemy& operator=(const IEnemy& other) = delete;
    IEnemy& operator=(IEnemy&& other) noexcept = delete;
    
    virtual void Update(float elapsedSec) override;

    virtual bool IsAwake() const final;

protected:
    virtual void Awake();
    virtual void Wait(float elapsedSec);
    virtual void Walk(float elapsedSec);
    virtual void Jump(float elapsedSec);
    virtual void Shoot(float elapsedSec);
    virtual void Fly(float elapsedSec);
    virtual void Spawn();
    virtual float GetAngle() const final;
    virtual bool IsFlipped() const final;
protected:
    Player* m_pPlayer;
    Sprite* m_pFX;
    const Point2f m_SpawnPos;
    int m_Score;
    int m_Health;
    bool m_Awake;
    bool m_AwakeFired;
    float m_AwakeDistance;
    float m_HorVelocity;
    float m_VerVelocity;
};
