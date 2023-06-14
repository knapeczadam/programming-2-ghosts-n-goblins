// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Player.h"

#include "IEnemy.h"
#include "Matrix2x3.h"
#include "Texture.h"
#include "utils.h"
#include "WoodyPig.h"
#include "collectibles/ICollectible.h"
#include "collectibles/Key.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/Camera.h"
#include "game/CameraManager.h"
#include "game/CollectibleManager.h"
#include "game/GameController.h"
#include "game/InputManager.h"
#include "game/LevelManager.h"
#include "game/Macros.h"
#include "game/PlayerManager.h"
#include "level/Level.h"
#include "throwables/Dagger.h"
#include "throwables/Lance.h"
#include "throwables/Torch.h"

#include <iostream>
#include <numeric>

Player::Player(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::C_ARTHUR, pos, true, pGameController}
      , m_HorVelocity{150.0f}
      , m_VerVelocity{100.0f}
      , m_JumpVelocity{500.0f}
      , m_Velocity{0.0f, 0.0f}
      , m_Acceleration{0.0f, -1391.0f} // -981.0f
      , m_State{State::IDLE}
      , m_Crouching{false}
      , m_ShortAccuCooldown{0.0f}
      , m_LongAccuCooldown{0.0f}
      , m_ShortCooldownTime{0.25f}
      , m_LongCooldownTime{0.30f}
      , m_Attacking{false}
      , m_CurrWeapon{Game::Label::T_LANCE}
      , m_Overheated{false}
      , m_OnPlatform{false}
      , m_OffsetSnapshot{0.0f, 0.0f}
      , m_CanJump{true}
      , m_MaxHP{2}
      , m_HP{m_MaxHP}
      , m_MaxLives{7}
      , m_Lives{3}
      , m_Score{0}
      , m_CanClimb{false}
      , m_Climbing{false}
      , m_OnLadder{false}
      , m_OnGround{false}
      , m_ImpactFromLeft{false}
      , m_HitTriggered{false}
      , m_HasKey{false}
      , m_OnHill{false}
      , m_Frog{false}
{
}

bool Player::IsOnHill() const
{
    return m_OnHill;
}

void Player::Draw() const
{
    GameObject::Draw();

#if DEBUG_RAYCAST
    const float epsilon{0.0f};
    Point2f playerCenter{GetColliderCenter()};
    // LEFT
    Point2f left;
    left.x = GetCollider().left - epsilon;
    left.y = playerCenter.y;
    // RIGHT
    Point2f right;
    right.x = GetCollider().left + GetCollider().width + epsilon;
    right.y = playerCenter.y;
    // DOWN
    Point2f down;
    down.x = playerCenter.x;
    down.y = GetCollider().bottom - epsilon;
    // UP
    Point2f up;
    up.x = playerCenter.x;
    up.y = GetCollider().bottom + GetCollider().height * 2 + epsilon;
    utils::SetColor(Color4f{0, 1, 0, 1});
    utils::DrawLine(playerCenter, left);
    utils::SetColor(Color4f{1, 0, 0, 1});
    utils::DrawLine(playerCenter, right);
    utils::SetColor(Color4f{1, 1, 0, 1});
    utils::DrawLine(Point2f{up.x, down.y + 2.0f}, up);
    utils::SetColor(Color4f{0, 0, 1, 1});
    utils::DrawLine(playerCenter, down);
#endif
}

void Player::UpdateSprite() const
{
    int leftOffset{1};
    switch (m_State)
    {
    case State::IDLE:
        m_pSprite->SetTopOffsetRows(0);
        m_pSprite->SetSubCols(1);
        break;
    case State::RUNNING:
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetSubCols(4);
        m_pSprite->SetFramesPerSec(16);
        leftOffset = 4;
        break;
    case State::JUMPING_RUNNING:
        m_pSprite->SetTopOffsetRows(2);
        m_pSprite->SetSubCols(1);
        break;
    case State::JUMPING_STANDING:
        m_pSprite->SetTopOffsetRows(3);
        m_pSprite->SetSubCols(1);
        break;
    case State::CROUCHING:
        m_pSprite->SetTopOffsetRows(4);
        m_pSprite->SetSubCols(1);
        break;
    case State::ATTACKING_NORMAL:
        m_pSprite->SetTopOffsetRows(5);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetFramesPerSec(8);
        leftOffset = 2;
        break;
    case State::ATTACKING_CROUCHING:
        m_pSprite->SetTopOffsetRows(6);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetFramesPerSec(8);
        leftOffset = 2;
        break;
    case State::CLIMBING:
        m_pSprite->SetTopOffsetRows(7);
        m_pSprite->SetSubCols(2);
        if (m_Climbing)
        {
            m_pSprite->SetFramesPerSec(4);
        }
        else
        {
            m_pSprite->SetFramesPerSec(0);
        }
        leftOffset = 2;
        break;
    case State::CLIMBING_TOP:
        leftOffset = 2;
        break;
    case State::HIT:
        m_pSprite->SetTopOffsetRows(10);
        if (m_HP == 1)
        {
            m_pSprite->SetLeftOffsetCols(0);
        }
        else
        {
            m_pSprite->SetLeftOffsetCols(2);
        }
        m_pSprite->SetSubCols(2);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->SetFramesPerSec(6);
        m_pSprite->CalculateFrameTime();
        m_pSprite->UpdateSourceRect();
        return;
    case State::DEAD_SKELETON:
        m_pSprite->SetTopOffsetRows(11);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(3);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->SetFramesPerSec(3);
        m_pSprite->CalculateFrameTime();
        m_pSprite->UpdateSourceRect();
        return;
    case State::DEAD_SKULL:
        m_pSprite->SetTopOffsetRows(11);
        m_pSprite->SetLeftOffsetCols(3);
        m_pSprite->SetSubCols(1);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->UpdateSourceRect();
        return;
    case State::FROG_IDLE:
        m_pSprite->SetTopOffsetRows(12);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubCols(1);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->UpdateSourceRect();
        return;
    case State::FROG_MOVING:
        m_pSprite->SetTopOffsetRows(13);
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(3);
        m_pSprite->SetCurrRowsCols();
        m_pSprite->SetFramesPerSec(6);
        m_pSprite->CalculateFrameTime();
        m_pSprite->UpdateSourceRect();
        return;
    }
    const int offsetMultiplier{m_HP - 1};
    m_pSprite->SetLeftOffsetCols(leftOffset * offsetMultiplier);
    m_pSprite->SetSubRows(1);
    m_pSprite->SetCurrRowsCols();
    m_pSprite->CalculateFrameTime();
    m_pSprite->UpdateSourceRect();
}

void Player::Update(float elapsedSec)
{
    switch (m_State)
    {
    case State::HIT:
        OnHit(elapsedSec);
        break;
    case State::DEAD_SKULL:
        StartTimer(0.8f);
        if (IsTimerFinished())
        {
            m_Active = false;
            DecreaseLives();
        }
        break;
    case State::DEAD_SKELETON:
        break;
    case State::FROG_IDLE:
    case State::FROG_MOVING:
        UpdateFrogPosition(elapsedSec);
        break;
    default:
        Attack();
        UpdateCooldown(elapsedSec);
        UpdatePosition(elapsedSec);
        break;
    }
}

void Player::LateUpdate(float elapsedSec)
{
    UpdateState();
    UpdateSprite();
    GameObject::LateUpdate(elapsedSec);
}

void Player::UpdateCooldown(float elapsedSec)
{
    if (m_Overheated)
    {
        m_LongAccuCooldown -= elapsedSec;
        if (m_LongAccuCooldown > 0)
        {
            return;
        }
        m_LongAccuCooldown = 0;
        m_Overheated = false;
    }
    if (m_Attacking)
    {
        m_ShortAccuCooldown -= elapsedSec;
        if (m_ShortAccuCooldown < 0)
        {
            m_ShortAccuCooldown = 0;
            m_Attacking = false;
        }
    }
    else
    {
        m_LongAccuCooldown -= elapsedSec;
        if (m_LongAccuCooldown >= m_LongCooldownTime)
        {
            m_Overheated = true;
        }
    }
}

void Player::Throw()
{
    for (GameObject* pWeapon : m_pGameController->m_pPlayerManager->GetThrowables())
    {
        if (pWeapon->GetLabel() == m_CurrWeapon and not pWeapon->IsActive())
        {
            Point2f pos{GetColliderCenter()};
            pWeapon->SetPosition(pos);
            pWeapon->SetFlipped(m_Flipped);
            pWeapon->Reset();
            return;
        }
    }
    switch (m_CurrWeapon)
    {
    case Game::Label::T_DAGGER:
        m_pGameController->m_pPlayerManager->GetThrowables().push_back(new Dagger{
            GetColliderCenter(), m_Flipped, false, m_pGameController
        });
        break;
    case Game::Label::T_LANCE:
        m_pGameController->m_pPlayerManager->GetThrowables().push_back(
            new Lance{GetColliderCenter(), m_Flipped, false, m_pGameController});
        break;
    case Game::Label::T_TORCH:
        m_pGameController->m_pPlayerManager->GetThrowables().push_back(
            new Torch{GetColliderCenter(), m_Flipped, false, m_pGameController});
        break;
    }
}

/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Controls
 * You can place up to either two or three instances of your weapon on-screen at once, depending on which you have equipped.
 * Press fire while crouching to throw a weapon low to the ground.
 * Rapidly tap the direction you are facing, while standing, in tandem with the fire button to increase your rate of fire.
 */
void Player::Attack()
{
    if (m_OnLadder) return;
    if (not m_Attacking and m_pGameController->m_pInputManager->IsPressed(Game::Label::I_ATTACK) and not
        m_pGameController->m_pInputManager->IsTriggered(Game::Label::I_ATTACK))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_ATTACK, true);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_THROW);
        m_ShortAccuCooldown += m_ShortCooldownTime;
        m_LongAccuCooldown += m_LongCooldownTime;
        m_Attacking = true;

        Throw();
    }
}

void Player::UpdatePosition(float elapsedSec)
{
    m_OnGround = m_pGameController->m_pLevelManager->GetLevel()->IsOnGround(this);
    if (m_OnGround)
    {
        Move();
        m_OnLadder = false;
        m_Climbing = false;
    }
    if (m_OnGround and m_CanClimb or m_OnLadder)
    {
        Climb();
    }
    if (not m_OnLadder)
    {
        ApplyGravity(elapsedSec);
    }
    if (m_OnPlatform)
    {
        SyncWithPlatform(elapsedSec);
    }
    else
    {
        m_OffsetSnapshot = Vector2f{0, 0};
        if (not m_Climbing)
        {
            m_Shape.left += m_Velocity.x * elapsedSec; // TODO: in else statement?
        }
    }
    m_Shape.bottom += m_Velocity.y * elapsedSec;

    CheckBoundaries(m_pGameController->m_pCameraManager->GetCamera()->GetBoundaries());
}

void Player::Move()
{
    Crouch();
    if (m_Crouching or m_Attacking)
    {
        Jump();
        m_Velocity.x = 0;
    }
    else
    {
        Jump();
        MoveHorizontal();
    }
}

void Player::MoveFrog()
{
    Jump();
    MoveHorizontal();
}

void Player::MoveHorizontal()
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_LEFT))
    {
        m_Velocity.x = -m_HorVelocity;
        m_Flipped = true;
    }
    else if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_RIGHT))
    {
        m_Velocity.x = m_HorVelocity;
        m_Flipped = false;
    }
    else
    {
        m_Velocity.x = 0;
    }
}

/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Controls
 * Use in conjunction with left or right to make Arthur jump in a particular direction.
 * Note that a Jump in this game is a 100% commitment; there is no reversing or manipulating a mid-air jump.
 */
void Player::Jump()
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_JUMP) and not m_pGameController->m_pInputManager->
        IsTriggered(Game::Label::I_JUMP))
    {
        m_pGameController->m_pInputManager->SetTriggered(Game::Label::I_JUMP, true);
        if (m_Frog)
        {
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_JUMP_FROG);
        }
        else
        {
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_JUMP);
        }
        m_Velocity.y = m_JumpVelocity;
        m_CanJump = false;
    }
    else
    {
        m_Velocity.y = 0;
    }
}

void Player::UpdateFrogPosition(float elapsedSec)
{
    m_OnGround = m_pGameController->m_pLevelManager->GetLevel()->IsOnGround(this);
    if (m_OnGround)
    {
        MoveFrog();
    }
    ApplyGravity(elapsedSec);
    if (m_OnPlatform)
    {
        SyncWithPlatform(elapsedSec);
    }
    else
    {
        m_OffsetSnapshot = Vector2f{0, 0};
        m_Shape.left += m_Velocity.x * elapsedSec; // TODO: in else statement?
    }
    m_Shape.bottom += m_Velocity.y * elapsedSec;

    CheckBoundaries(m_pGameController->m_pCameraManager->GetCamera()->GetBoundaries());
}

void Player::Crouch()
{
    if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_DOWN))
    {
        m_Crouching = true;
    }
    else
    {
        m_Crouching = false;
    }
}

void Player::Climb()
{
    if (not m_OnHill and m_pGameController->m_pInputManager->IsPressed(Game::Label::I_UP))
    {
        m_Velocity.y = m_VerVelocity;
        m_Climbing = true;
    }
    else if (m_pGameController->m_pInputManager->IsPressed(Game::Label::I_DOWN))
    {
        m_Velocity.y = -m_VerVelocity;
        m_Climbing = true;
    }
    else
    {
        m_Velocity.y = 0.0f;
        m_Climbing = false;
    }
}

void Player::ApplyGravity(float elapsedSec)
{
    m_Velocity += m_Acceleration * elapsedSec;
}

void Player::SyncWithPlatform(float elapsedSec)
{
    if (m_OffsetSnapshot == Vector2f{0, 0})
    {
        m_OffsetSnapshot.x = GetPosition<Point2f>().x - m_pGameController->m_pLevelManager->GetPlatform()->GetPosition<
            Point2f>().x;
        m_OffsetSnapshot.y = m_Shape.bottom - m_pGameController->m_pLevelManager->GetPlatform()->GetPosition<Point2f>().
                                                                 y;
    }
    m_OffsetSnapshot.x += m_Velocity.x * elapsedSec;
    Matrix2x3 pos{};
    Matrix2x3 T2{Matrix2x3::CreateTranslationMatrix(m_OffsetSnapshot)};
    Matrix2x3 T1{
        Matrix2x3::CreateTranslationMatrix(m_pGameController->m_pLevelManager->GetPlatform()->GetPosition<Vector2f>())
    };
    pos = T1 * T2 * pos;
    m_Shape.left = pos.orig.x;
}

void Player::UpdateFrog()
{
    StartTimer(5.0f);
    if (IsTimerFinished())
    {
        m_State = State::IDLE;
        m_Frog = false;
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_TRANSFORM);
    }
    if (m_Velocity == Vector2f{})
    {
        m_State = State::FROG_IDLE;
    }
    else
    {
        m_State = State::FROG_MOVING;
    }
}

void Player::UpdateState()
{
    // std::numeric_limits<float>::epsilon()
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};
    const float absVelX{std::abs(m_Velocity.x)};
    const float absVelY{std::abs(m_Velocity.y)};

    if (m_State == State::HIT or m_State == State::DEAD_SKULL) return;
    if (m_Frog)
    {
        UpdateFrog();
        return;
    }
    else if (m_State == State::DEAD_SKELETON)
    {
        if (m_pSprite->IsLastFrame())
        {
            m_State = State::DEAD_SKULL;
        }
        return;
    }
    else if (m_HP == 0)
    {
        m_State = State::DEAD_SKELETON;
        m_pSprite->ResetCurrFrame();
        return;
    }
    else if (not m_Crouching and m_Velocity == Vector2f{})
    {
        m_State = State::IDLE;
    }
    else if (absVelX > 0.0f and absVelY < epsilon)
    {
        m_State = State::RUNNING;
    }
    else if (absVelX > 0.0f and absVelY > epsilon)
    {
        m_State = State::JUMPING_RUNNING;
        m_Crouching = false;
        m_CanClimb = false;
    }
    else if (absVelX < epsilon and absVelY > epsilon)
    {
        m_State = State::JUMPING_STANDING;
        m_Crouching = false;
        m_CanClimb = false;
    }

    if (m_Crouching)
    {
        m_State = State::CROUCHING;
    }

    if (m_Attacking)
    {
        if (m_Crouching)
        {
            m_State = State::ATTACKING_CROUCHING;
        }
        else
        {
            m_State = State::ATTACKING_NORMAL;
        }
    }
    m_OnHill = m_Collider.bottom >= LevelManager::GetHillHeight();

    if (m_OnHill)
    {
        m_OnLadder = false;
    }

    if (m_OnLadder)
    {
        m_State = State::CLIMBING;
    }
}

// TODO: köze van a CheckForBoundaries függvényhez
void Player::UpdateCollider()
{
    if (m_Crouching)
    {
        SetColliderHeight(44.0f);
    }
    else
    {
        ResetCollider();
    }
    GameObject::UpdateCollider();
}

std::string Player::ToString(State state) const
{
    switch (state)
    {
    case State::IDLE:
        return "IDLE";
    case State::RUNNING:
        return "RUNNING";
    case State::JUMPING_STANDING:
        return "JUMPING_STANDING";
    case State::JUMPING_RUNNING:
        return "JUMPING_RUNNING";
    case State::CROUCHING:
        return "CROUCHING";
    case State::ATTACKING_NORMAL:
        return "ATTACKING_NORMAl";
    case State::ATTACKING_CROUCHING:
        return "ATTACKING_CROUCHING";
    case State::CLIMBING:
        return "CLIMBING";
    case State::CLIMBING_TOP:
        return "CLIMBING_TOP";
    case State::HIT:
        return "HIT";
    case State::DEAD_SKELETON:
        return "DEAD_SKELETON";
    case State::DEAD_SKULL:
        return "DEAD_SKULL";
    case State::TRANSFORMING:
        return "TRANSFORMING";
    case State::FROG_IDLE:
        return "FROG_IDLE";
    case State::FROG_MOVING:
        return "FROG_MOVING";
    default:
        return "UNKNOWN";
    }
}

std::string Player::ToString(Game::Label weapon) const
{
    switch (weapon)
    {
    case Game::Label::T_LANCE:
        return "LANCE";
    case Game::Label::T_DAGGER:
        return "DAGGER";
    case Game::Label::T_TORCH:
        return "TORCH";
    default:
        return "UNKNOWN";
    }
}

bool Player::IsAttacking() const
{
    return m_Attacking;
}

void Player::CanJump(bool canJump)
{
    m_CanJump = canJump;
}

void Player::CanClimb(bool canClimb)
{
    m_CanClimb = canClimb;
}

bool Player::HasKey() const
{
    return m_HasKey;
}

Vector2f Player::GetVelocity() const
{
    return m_Velocity;
}

void Player::SetVelocity(const Vector2f& velocity)
{
    m_Velocity = velocity;
}

void Player::SetIsOnPlatform(bool isOnPlatform)
{
    m_OnPlatform = isOnPlatform;
}

int Player::GetHP() const
{
    return m_HP;
}

void Player::SetHP(int hp)
{
    m_HP = hp;
}

int Player::GetLives() const
{
    return m_Lives;
}

void Player::SetLives(int lives)
{
    m_Lives = lives;
}

int Player::GetMaxLives() const
{
    return m_MaxLives;
}

Game::Label Player::GetWeapon() const
{
    return m_CurrWeapon;
}

void Player::SetWeapon(Game::Label weapon)
{
    m_CurrWeapon = weapon;
}

int Player::GetScore() const
{
    return m_Score;
}

void Player::SetScore(int score)
{
    m_Score = score;
}

void Player::AddScore(int score)
{
    m_Score += score;
}

bool Player::HandleEnemy(GameObject* other)
{
    IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
    if (pEnemy)
    {
        if (pEnemy->GetLabel() == Game::Label::C_ZOMBIE and pEnemy->IsAwake()) return true;
        if (pEnemy->GetLabel() == Game::Label::C_WOODY_PIG)
        {
            const WoodyPig* pWoodyPig{static_cast<WoodyPig*>(other)};
            if (pWoodyPig->GetState() == WoodyPig::State::SPAWNING) return true;
        }
        if (m_HP > 0 and m_State != State::HIT)
        {
            m_State = State::HIT;
            m_ImpactFromLeft = ImpactFromLeft(other);
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_HIT);
            DecreaseHP();
            if (m_HP == 1)
            {
                m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_DAMAGE, GetColliderCenter(), m_Flipped);
            }
        }
        return true;
    }
    return false;
}

bool Player::HandleThrowable(GameObject* other)
{
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(other)};
    if (pThrowable)
    {
        other->SetActive(false);
        other->SetVisible(false);
        switch (other->GetLabel())
        {
        case Game::Label::T_DAGGER:
            m_CurrWeapon = Game::Label::T_DAGGER;
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WEAPON_PICKUP);
            m_pGameController->m_pCollectibleManager->DeactivateContent();
            break;
        case Game::Label::T_LANCE:
            m_CurrWeapon = Game::Label::T_LANCE;
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WEAPON_PICKUP);
            m_pGameController->m_pCollectibleManager->DeactivateContent();
            break;
        case Game::Label::O_TORCH:
            m_CurrWeapon = Game::Label::T_TORCH;
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_WEAPON_PICKUP);
            m_pGameController->m_pCollectibleManager->DeactivateContent();
            break;
        case Game::Label::T_EYEBALL:
        case Game::Label::T_SPEAR_X:
        case Game::Label::T_SPEAR_Y:
        case Game::Label::T_FIREBALL_UNICORN:
        case Game::Label::T_FIREBALL_RED_ARREMER:
            if (m_HP > 0 and m_State != State::HIT)
            {
                m_State = State::HIT;
                m_ImpactFromLeft = ImpactFromLeft(other);
                m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_HIT);
                DecreaseHP();
            }
            break;
        case Game::Label::T_SPELL:
            m_State = State::FROG_IDLE;
            m_Frog = true;
            ResetTimer();
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_TRANSFORM);
            break;
        }
        return true;
    }
    return false;
}

bool Player::HandleCollectible(GameObject* other)
{
    ICollectible* pCollectable{dynamic_cast<ICollectible*>(other)};
    if (pCollectable)
    {
        if (other->GetLabel() == Game::Label::O_POT) return false;

        switch (other->GetLabel())
        {
        case Game::Label::O_KEY:
            // https://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
            {
                Key* pKey{static_cast<Key*>(other)};
                if (pKey->IsOnGround())
                {
                    m_Score += pCollectable->GetScore();
                    m_HasKey = true;
                    other->SetVisible(false);
                    other->SetActive(false);
                }
            }
            break;
        case Game::Label::O_ARMOR:
            other->SetVisible(false);
            other->SetActive(false);
            ++m_HP;
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_ARMOR_PICKUP);
            break;
        case Game::Label::O_DOLL:
        case Game::Label::O_KING:
        case Game::Label::O_NECKLACE:
            m_pGameController->m_pCollectibleManager->DeactivateContent();
        default:
            other->SetVisible(false);
            other->SetActive(false);
            m_Score += pCollectable->GetScore();
            m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_SCORE, other->GetColliderCenter(), false,
                                                        other);
            m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_TREASURE_PICKUP);
            break;
        }
        return true;
    }
    return false;
}

Player::State Player::GetState() const
{
    return m_State;
}

void Player::SetState(State state)
{
    m_State = state;
}

void Player::IncreaseLives()
{
    if (m_Lives < m_MaxLives)
    {
        ++m_Lives;
    }
}

void Player::DecreaseLives()
{
    if (m_Lives > 0)
    {
        --m_Lives;
    }
}

void Player::OnHit(float elapsedSec)
{
    if (not m_HitTriggered)
    {
        m_Velocity.y = m_JumpVelocity;;
        m_HitTriggered = true;
        m_Frog = false;
    }
    m_Velocity.x = m_ImpactFromLeft ? m_HorVelocity : -m_HorVelocity;
    ApplyGravity(elapsedSec);
    m_Shape.bottom += m_Velocity.y * elapsedSec;
    m_Shape.left += m_Velocity.x * elapsedSec;
    UpdateCollider();
    if (m_pGameController->m_pLevelManager->GetLevel()->IsOnGround(this))
    {
        m_Flipped = not m_Flipped;
        m_Velocity.x = 0;
        m_HitTriggered = false;
        if (m_HP == 0)
        {
            m_State = State::DEAD_SKELETON;
            m_pSprite->ResetCurrFrame();
        }
        else
        {
            m_State = State::IDLE;
        }
    }
}

void Player::Die()
{
    m_HP = 0;
    m_State = State::DEAD_SKELETON;
    m_pSprite->ResetCurrFrame();
}

bool Player::ImpactFromLeft(GameObject* other) const
{
    return other->GetColliderCenter().x < GetColliderCenter().x;
}

void Player::SetOnLadder(bool onLadder)
{
    m_OnLadder = onLadder;
}

bool Player::IsClimbing() const
{
    return m_Climbing;
}

bool Player::IsAlive() const
{
    return m_HP > 0;
}

void Player::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;

    if (HandleEnemy(other)) return;
    if (HandleThrowable(other)) return;
    if (HandleCollectible(other)) return;
}

void Player::CheckBoundaries(const Rectf& boundaries)
{
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetColliderWidth()) / 2};
    const float epsilon{1.0f};
    if (m_Collider.left < boundaries.left)
    {
        m_Shape.left = boundaries.left - horizontalOffset;
    }
    else if (m_Collider.left + m_Collider.width > boundaries.width)
    {
        m_Shape.left = boundaries.width - m_Collider.width - horizontalOffset;
    }
}

void Player::DecreaseHP()
{
    if (m_HP > 0)
    {
        --m_HP;
    }
}
