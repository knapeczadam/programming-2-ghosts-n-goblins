// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include "game/GameObject.h"


/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Arthur
 * You control Arthur throughout his quest to reach Astaroth's chamber at the top of his guarded castle, and rescue his love, the Princess PrinPrin.
 * Arthur can run and jump, as well as throw a number of weapons at his enemies.
 * Arthur cannot withstand the attacks of the monsters very well, but his armor will protect him from one hit.
 * He begins each stage and each new life with a full set of armor on.
 * However, if he is struck while wearing the armor, the armor will fall to pieces, and he will be left to fight against Astaroth's legions in nothing but his boxers, as depicted to the right.
 * While in this state, if just one enemy touches him, Arthur is doomed and loses one life.
 * It is possible to find and collect armor when Arthur is without any, but they are usually hidden from sight.
 */
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
    explicit Player(const Point2f& pos,  GameController* pGameController);
    virtual ~Player() override = default;
    Player(const Player& other) = delete;
    Player(Player&& other) noexcept = delete;
    Player& operator=(const Player& other) = delete;
    Player& operator=(Player&& other) noexcept = delete;

    virtual void Draw() const override;
    void UpdateCooldown(float elapsedSec);
    void Throw();
    virtual void Update(float elapsedSec) override;
    virtual void LateUpdate(float elapsedSec) override;
    void SyncWithPlatform(float elapsedSec);
    virtual void HandleCollision(GameObject* other) override;
    void UpdateSprite() const; // TODO

    void Attack();
    bool IsAttacking() const;
    void CanJump(bool canJump);
    void CanClimb(bool canClimb);

    Vector2f GetVelocity() const;
    void SetVelocity(const Vector2f& velocity);
    void SetIsOnPlatform(bool isOnPlatform);
    int GetLives() const;
    Game::Label GetWeapon() const;
    int GetScore() const;
    void AddScore(int score);

    void UpdateState();
protected:
    virtual void UpdateCollisionBox() override;

private:
    void UpdatePosition(float elapsedSec);
    
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
    float m_JumpVelocity;
    Vector2f m_Velocity;
    Vector2f m_Acceleration;
    State m_State;
    bool m_Crouching;
    float m_ShortAccuCooldown;
    float m_LongAccuCooldown;
    float m_ShortCooldownTime;
    float m_LongCooldownTime;
    bool m_Attacking;
    Game::Label m_CurrWeapon;
    bool m_Overheated;
    bool m_OnPlatform;
    Vector2f m_OffsetSnapshot;
    bool m_CanJump;
    int m_Lives;
    const int m_MaxLives;
    int m_Score;
    bool m_CanClimb;
    bool m_Climbing;
    bool m_OnLadder;
    bool m_OnGround;
};
