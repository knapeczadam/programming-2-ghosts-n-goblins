// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include "game/GameObject.h"


class Player : public GameObject
{
public:
    enum class State
    {
        idle,
        running,
        jumping_running,
        jumping_standing,
        crouching,
        attacking_normal,
        attacking_crouching,
        climbing,
        climbing_top
    };

public:
    Player(Sprite* pSprite, const Point2f& pos, Level* pLevel);
    virtual ~Player() override = default;
    Player(const Player& other) = delete;
    Player(Player&& other) noexcept = delete;
    Player& operator=(const Player& other) = delete;
    Player& operator=(Player&& other) noexcept = delete;

    void UpdateCooldown(float elapsedSec);
    virtual void Update(float elapsedSec) override;
    void SyncWithPlatform(float elapsedSec);
    virtual void HandleCollision(GameObject* other) override;
    void valamiMegNemTom() const;

    void Attack(std::vector<IThrowable*>& throwables, SpriteFactory* spriteFactory);
    bool IsAttacking() const;
    void CanJump(bool canJump);

    Vector2f GetVelocity() const;
    void SetVelocity(const Vector2f& velocity);
    void SetIsOnPlatform(bool isOnPlatform);

private:
    void UpdatePosition(float elapsedSec);
    void UpdateState();
    
    void Move(float elapsedSec, const Uint8* pState);
    void MoveHorizontal(const Uint8* pState);
    void Jump(const Uint8* pState);
    void Crouch(const Uint8* pState);
    void Climb(const Uint8* pState);
    void ApplyGravity(float elapsedSec);
    
    void CheckForBoundaries(const Rectf& boundaries);
    
public:
    static Point2f GetSpawnPos();
private:
    static const Point2f m_SpawnPos;
    
    float m_HorVelocity;
    float m_VerVelocity;
    Vector2f m_Velocity;
    Vector2f m_Acceleration;
    State m_State;
    Level* m_pLevel;
    bool m_IsCrouching;
    float m_ShortAccuCooldown;
    float m_LongAccuCooldown;
    float m_ShortCooldownTime;
    float m_LongCooldownTime;
    bool m_isAttacking;
    Game::Label m_CurrWeapon;
    bool m_Overheated;
    bool m_IsOnPlatform;
    Vector2f m_OffsetSnapshot;
    bool m_CanJump;
};
