// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"

class Level;
class Texture;
class Sprite;

class Avatar final
{
public:
    enum class ActionState
    {
        waiting,
        moving,
        transforming
    };

public:
    explicit Avatar();
    explicit Avatar(Texture* pTexture);
    explicit Avatar(Sprite* pSprite);
    Avatar(const Avatar& other) = delete;
    Avatar(Avatar&& other) noexcept = delete;
    Avatar& operator=(const Avatar& other) = delete;
    Avatar& operator=(Avatar&& other) noexcept = delete;
    ~Avatar();
    
    void Draw() const;
    void Update(float elapsedSec, const Level& level);
    Rectf GetShape() const;
    void PowerUpHit();

private:
    void DrawSprite() const;
    void UpdatePosition(float elapsedSec, const Level& level);
    void UpdateState();
    void DrawRect() const;
    void UpdateAnimation(float elapsedSec);
    void MoveHorizontal(const Uint8* pState, float elapsedSec);
    void MoveVertical(const Uint8* pState, float elapsedSec);
    void ApplyGravity(float elapsedSec);
    void MoveAvatar(float elapsedSec, const Uint8* pState);
    void Transform(float elapsedSec);
    void IncreasePower();
    void DrawPower() const;
    void SetStateColor() const;
    void CheckForBoundaries(const Rectf& boundaries);
    void FlipSrpite(const Rectf& dst, const Rectf& src) const;

private:
    Rectf m_Shape;
    float m_HorSpeed;
    float m_JumpSpeed;
    Vector2f m_Velocity;
    Vector2f m_Acceleration;
    ActionState m_ActionState;
    float m_AccuTransformSec;
    float m_MaxTransformSec;
    const int m_MaxPower;
    int m_Power;
    Texture* m_pSpritesTexture;
    const float m_ClipHeight;
    const float m_ClipWidth;
    const int m_NrOfFrames;
    const int m_NrFramesPerSec;
    float m_AnimTime;
    int m_AnimFrame;
    bool m_IsFlipped;
    Sprite* m_pSprite;
};
