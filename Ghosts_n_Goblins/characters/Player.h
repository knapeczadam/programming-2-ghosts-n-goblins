// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include "game/GameObject.h"

/**
 * \par Arthur 
 * You control Arthur throughout his quest to reach Astaroth's chamber at the top of his guarded castle, and rescue his love, the Princess PrinPrin.
 * Arthur can run and jump, as well as throw a number of weapons at his enemies.
 * Arthur cannot withstand the attacks of the monsters very well, but his armor will protect him from one hit.
 * He begins each stage and each new life with a full set of armor on.
 * However, if he is struck while wearing the armor, the armor will fall to pieces, and he will be left to fight against Astaroth's legions in nothing but his boxers, as depicted to the right.
 * While in this state, if just one enemy touches him, Arthur is doomed and loses one life.
 * It is possible to find and collect armor when Arthur is without any, but they are usually hidden from sight.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Arthur">StrategyWiki</a>
 */
class Player final : public GameObject
{
public:
    enum class State
    {
        IDLE,
        RUNNING,
        JUMPING_RUNNING,
        JUMPING_STANDING,
        CROUCHING,
        ATTACKING_NORMAL,
        ATTACKING_CROUCHING,
        CLIMBING,
        CLIMBING_TOP,
        HIT,
        DEAD_SKELETON,
        DEAD_SKULL,
        TRANSFORMING,
        FROG_IDLE,
        FROG_MOVING
    };

public:
    explicit Player(const Point2f& pos, GameController* pGameController);
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
    void UpdateFrog();
    virtual void HandleCollision(GameObject* other) override;
    void UpdateSprite() const; // TODO

    void Attack();
    bool IsAttacking() const;
    void CanJump(bool canJump);
    void CanClimb(bool canClimb);
    bool HasKey() const;

    Vector2f GetVelocity() const;
    void SetVelocity(const Vector2f& velocity);
    void SetIsOnPlatform(bool isOnPlatform);
    int GetHP() const;
    void SetHP(int hp);
    int GetLives() const;
    void SetLives(int lives);
    int GetMaxLives() const;
    Game::Label GetWeapon() const;
    void SetWeapon(Game::Label weapon);
    int GetScore() const;
    void SetScore(int score);
    void AddScore(int score);
    bool HandleEnemy(GameObject* other);
    bool HandleThrowable(GameObject* other);
    bool HandleCollectible(GameObject* other);
    State GetState() const;
    void SetState(State state);
    void IncreaseLives();
    void DecreaseLives();
    void OnHit(float elapsedSec);
    void Die();
    bool ImpactFromLeft(GameObject* other) const;
    void SetOnLadder(bool onLadder);
    bool IsClimbing() const;
    bool IsAlive() const;
    bool IsOnHill() const;

    void UpdateState();
    virtual void UpdateCollider() override;

    std::string ToString(State state) const;
    std::string ToString(Game::Label weapon) const;

private:
    void UpdatePosition(float elapsedSec);
    void UpdateFrogPosition(float elapsedSec);

    void Move();
    void MoveFrog();
    void MoveHorizontal();
    void Jump();
    void Crouch();
    void Climb();
    void ApplyGravity(float elapsedSec);

    void CheckBoundaries(const Rectf& boundaries);
    void DecreaseHP();

private:
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
    const int m_MaxHP;
    int m_HP;
    const int m_MaxLives;
    int m_Lives;
    int m_Score;
    bool m_CanClimb;
    bool m_Climbing;
    bool m_OnLadder;
    bool m_OnGround;
    bool m_ImpactFromLeft;
    bool m_HitTriggered;
    bool m_HasKey;
    bool m_OnHill;
    bool m_Frog;
};
