// Knapecz, Adam - 1DAE11
#pragma once
#include "game/Game.h"
#include "game/GameObject.h"

class Platform final : public GameObject
{
public:
    explicit Platform(const Point2f& pos, GameController* pGameController);
    virtual ~Platform() override = default;
    Platform(const Platform& other) = delete;
    Platform(Platform&& other) noexcept = delete;
    Platform& operator=(const Platform& other) = delete;
    Platform& operator=(Platform&& other) noexcept = delete;

    void Move();
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    bool IsOnGround(GameObject* pGameObject) const;

private:
    std::vector<Point2f> m_Vertices;
    float m_AccuSec;
    const Point2f m_OriginalPos;
    float m_Speed;
    const float m_MaxAmplitude;
    const float m_ShortAmplitude;
    float m_CurrAmplitude;
    bool m_Shortened;
    bool m_Flip;
};
