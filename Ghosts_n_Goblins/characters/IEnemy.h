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

    virtual int GetScore() const final;
    virtual void Reset() override;
    virtual void ResetHP() final;
    virtual bool IsFixedDirection() const final;
    virtual void SetSpawnPosition(const Point2f& position) final;

protected:
    virtual void Wait(float elapsedSec);
    virtual void Walk(float elapsedSec);
    virtual void Jump(float elapsedSec);
    virtual void Shoot(float elapsedSec);
    virtual void Fly(float elapsedSec);
    virtual void Spawn(float elapsedSec);
    virtual float GetAngle() const final;
    virtual bool IsFlipped() const override;
    virtual void Switch(float interval);
    virtual void Ping();
    virtual void Pong();

protected:
    Point2f m_SpawnPosition;
    int m_Score;
    int m_HP;
    int m_OriginalHP;
    float m_HorVelocity;
    float m_VerVelocity;
    bool m_Ping;
    bool m_FixedDirection;
};
