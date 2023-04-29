// Knapecz, Adam - 1DAE11
#pragma once
#include "Vector2f.h"
#include <vector>
#include "game/Game.h"
#include "game/GameObject.h"

class Texture;

class Platform : public GameObject
{
public:
    Platform(Sprite* pSprite, const Point2f& pos);
    virtual ~Platform() override = default;
    Platform(const Platform& other) = delete;
    Platform(Platform&& other) noexcept = delete;
    Platform& operator=(const Platform& other) = delete;
    Platform& operator=(Platform&& other) noexcept = delete;
    
    virtual void Draw() const override;
    void Move();
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* pGameObject) override;
    bool IsOnGround(GameObject* pGameObject) const;

private:
    void InitVertices();
    void UpdateVertices();

private:
    std::vector<Point2f> m_Vertices;
    float m_AccuSec;
    const Point2f m_OriginalPos;
    float m_Speed;
    const float m_MaxAmplitude;
    const float m_ShortAmplitude;
    float m_CurrAmplitude;
    bool m_IsShortened;
    bool m_Flip;
    
};
