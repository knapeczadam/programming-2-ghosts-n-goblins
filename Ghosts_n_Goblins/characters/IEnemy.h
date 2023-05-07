#pragma once
#include "game/GameObject.h"

class IEnemy : public GameObject
{
public:
    explicit IEnemy(Game::Label label, const Point2f& pos, GameController* pGameController);
    virtual ~IEnemy() override = default;
    IEnemy(const IEnemy& other) = delete;
    IEnemy(IEnemy&& other) noexcept = delete;
    IEnemy& operator=(const IEnemy& other) = delete;
    IEnemy& operator=(IEnemy&& other) noexcept = delete;
    
    virtual void Update(float elapsedSec) override;

    virtual bool IsAwake() const final;
    virtual void SetAwake(bool awake) final;
    virtual int GetScore() const final;

protected:
    virtual void Awake();
    virtual void Wait(float elapsedSec);
    virtual void Walk(float elapsedSec);
    virtual void Jump(float elapsedSec);
    virtual void Shoot(float elapsedSec);
    virtual void Fly(float elapsedSec);
    virtual void Spawn();
    virtual float GetAngle() const final;
    virtual bool IsFlipped() const override;
    virtual void Switch(float interval);
    virtual void Ping();
    virtual void Pong();
protected:
    const Point2f m_SpawnPos;
    int m_Score;
    int m_Health;
    bool m_Awake;
    bool m_AwakeFired;
    float m_AwakeDistance;
    float m_HorVelocity;
    float m_VerVelocity;
    bool m_Ping;
};
