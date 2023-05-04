#pragma once
#include "game/GameObject.h"

class IEnemy : public GameObject
{
public:
    IEnemy(Game::Label label, Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager);
    virtual ~IEnemy() override = default;
    IEnemy(const IEnemy& other) = delete;
    IEnemy(IEnemy&& other) noexcept = delete;
    IEnemy& operator=(const IEnemy& other) = delete;
    IEnemy& operator=(IEnemy&& other) noexcept = delete;

protected:
    virtual void Wait();
    virtual void Walk();
    virtual void Jump();
    virtual void Shoot();
    virtual void Fly();
    virtual void Spawn();
    virtual float GetAngle() const final;
    virtual bool IsFlipped() const final;
protected:
    Player* m_pPlayer;
    SoundManager* m_pSoundManager;
    int m_Score;
    int m_Health;
};
