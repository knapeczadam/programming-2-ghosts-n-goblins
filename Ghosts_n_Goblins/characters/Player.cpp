// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Player.h"
#include "IEnemy.h"
#include "Matrix2x3.h"
#include "Texture.h"
#include "utils.h"
#include "collectibles/ICollectible.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/CollisionBox.h"
#include "game/Macros.h"
#include "level/IClimable.h"
#include "level/Level.h"
#include "level/Platform.h"
#include "throwables/Dagger.h"
#include "throwables/Lance.h"
#include "throwables/Torch.h"

#include <iostream>
#include <numeric>


const Point2f Player::m_SpawnPos{50.0f, 64.0f};

Player::Player(const Point2f& pos, std::vector<GameObject*>& throwables, Level* pLevel,
               SpriteFactory* pSpriteFactory, SoundManager* pSoundManager)
    : GameObject{Game::Label::C_ARTHUR, pos, true, pSpriteFactory, pSoundManager}
      , m_HorVelocity{150.0f}
      , m_VerVelocity{100.0f}
      , m_JumpVelocity{500.0f}
      , m_Velocity{0.0f, 0.0f}
      , m_Acceleration{0.0f, -1391.0f} // -981.0f
      , m_State{State::idle}
      , m_pLevel{pLevel}
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
      , m_Lives{7}
      , m_MaxLives{7}
      , m_Score{0}
      , m_CanClimb{false}
      , m_Climbing{false}
      , m_OnLadder{false}
      , m_OnGround{false}
      , m_PlayerThrowables{throwables}
{
}

void Player::Draw() const
{
    GameObject::Draw();

#if DEBUG_RAYCAST
    const float epsilon{0.0f};
    Point2f playerCenter{GetCollisionBoxCenter()};
    // LEFT
    Point2f left;
    left.x = GetCollisionBox().left - epsilon;
    left.y = playerCenter.y;
    // RIGHT
    Point2f right;
    right.x = GetCollisionBox().left + GetCollisionBox().width + epsilon;
    right.y = playerCenter.y;
    // DOWN
    Point2f down;
    down.x = playerCenter.x;
    down.y = GetCollisionBox().bottom - epsilon;
    utils::SetColor(Color4f{0, 1, 0, 1});
    utils::DrawLine(playerCenter, left);
    utils::SetColor(Color4f{1, 0, 0, 1});
    utils::DrawLine(playerCenter, right);
    utils::SetColor(Color4f{0, 0, 1, 1});
    utils::DrawLine(playerCenter, down);
#endif
}

void Player::UpdateSprite() const
{
    m_pSprite->SetTopOffsetRows(0);
    m_pSprite->SetLeftOffsetCols(0);

    switch (m_State)
    {
    case State::idle:
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(1);
        break;
    case State::running:
        m_pSprite->SetTopOffsetRows(1);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(4);
        m_pSprite->SetFramesPerSec(10);
        break;
    case State::jumping_running:
        m_pSprite->SetTopOffsetRows(2);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(1);
        break;
    case State::jumping_standing:
        m_pSprite->SetTopOffsetRows(3);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(1);
        break;
    case State::crouching:
        m_pSprite->SetTopOffsetRows(4);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(1);
        break;
    case State::attacking_normal:
        m_pSprite->SetTopOffsetRows(5);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetFramesPerSec(9);
        break;
    case State::attacking_crouching:
        m_pSprite->SetTopOffsetRows(6);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetFramesPerSec(9);
        break;
    case State::climbing:
        m_pSprite->SetTopOffsetRows(7);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(2);
        if (m_Climbing)
        {
            m_pSprite->SetFramesPerSec(4);
        }
        else
        {
            m_pSprite->SetFramesPerSec(0);
        }
        break;
    case State::climbing_top:
        break;
    }
    m_pSprite->SetFrameTime();
    m_pSprite->SetCurrRowsCols();
    m_pSprite->UpdateSourceRect();
}

void Player::Update(float elapsedSec)
{
    UpdateCooldown(elapsedSec);
    UpdatePosition(elapsedSec);
    UpdateCollisionBox();
}

void Player::LateUpdate(float elapsedSec)
{
    UpdateSprite();
    UpdateState();
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
    for (GameObject* pWeapon : m_PlayerThrowables)
    {
        if (pWeapon->GetLabel() == m_CurrWeapon and not pWeapon->IsActive())
        {
            pWeapon->SetPosition(GetShapeCenter());
            pWeapon->SetFlipped(m_Flipped);
            pWeapon->SetActive(true);
            pWeapon->SetVisible(true);
            return;
        }
    }
    switch (m_CurrWeapon)
    {
    case Game::Label::T_DAGGER:
        m_PlayerThrowables.push_back(new Dagger{GetShapeCenter(), m_Flipped, false, m_pSpriteFactory});
        break;
    case Game::Label::T_LANCE:
        m_PlayerThrowables.push_back(new Lance{GetShapeCenter(), m_Flipped, false, m_pSpriteFactory});
        break;
    case Game::Label::T_TORCH:
        m_PlayerThrowables.push_back(new Torch{GetShapeCenter(), m_Flipped, false, m_pSpriteFactory});
        break;
    }
}

void Player::Attack()
{
    if (not m_Attacking)
    {
        m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_THROW);
        m_ShortAccuCooldown += m_ShortCooldownTime;
        m_LongAccuCooldown += m_LongCooldownTime;
        m_Attacking = true;

        Throw();
    }
}

void Player::UpdatePosition(float elapsedSec)
{
    const Uint8* pState{SDL_GetKeyboardState(nullptr)};
    if (m_pLevel->IsOnGround(this))
    {
        Move(elapsedSec, pState);
        m_OnGround = true;
    }
    else
    {
        m_OnGround = false;
    }


    // if (m_CanClimb)
    // {
    //     Climb(pState);
    //     if (m_OnLadder)
    //     {
    //         m_State = State::climbing;
    //     }
    // }

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

    CheckForBoundaries(m_pLevel->GetBoundaries());
}

void Player::Move(float elapsedSec, const Uint8* pState)
{
    Crouch(pState);
    if (m_Crouching or m_Attacking)
    {
        Jump(pState);
        m_Velocity.x = 0;
    }
    else
    {
        Jump(pState);
        MoveHorizontal(pState);
    }
}

void Player::MoveHorizontal(const Uint8* pState)
{
    if (pState[SDL_SCANCODE_LEFT])
    {
        m_Velocity.x = -m_HorVelocity;
        m_Flipped = true;
    }
    else if (pState[SDL_SCANCODE_RIGHT])
    {
        m_Velocity.x = m_HorVelocity;
        m_Flipped = false;
    }
    else
    {
        m_Velocity.x = 0;
    }
}


void Player::Jump(const Uint8* pState)
{
    if (m_CanJump)
    {
        if (pState[SDL_SCANCODE_S])
        {
            m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_JUMP);
            m_Velocity.y = m_JumpVelocity;
            m_CanJump = false;
        }
        else
        {
            m_Velocity.y = 0;
        }
    }
}

void Player::Crouch(const Uint8* pState)
{
    if (pState[SDL_SCANCODE_DOWN])
    {
        m_Crouching = true;
    }
    else
    {
        m_Crouching = false;
    }
}

void Player::Climb(const Uint8* pState)
{
    if (pState[SDL_SCANCODE_UP])
    {
        m_Velocity.y = m_VerVelocity;
        m_State = State::climbing;
    }
    else if (pState[SDL_SCANCODE_DOWN])
    {
        if (not m_OnGround)
        {
            m_Velocity.y = -m_VerVelocity;
            m_State = State::climbing;
        }
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
        m_OffsetSnapshot.x = GetPosition<Point2f>().x - m_pLevel->GetPlatform()->GetPosition<Point2f>().x;
        m_OffsetSnapshot.y = m_Shape.bottom - m_pLevel->GetPlatform()->GetPosition<Point2f>().y;
    }
    m_OffsetSnapshot.x += m_Velocity.x * elapsedSec;
    Matrix2x3 pos{};
    Matrix2x3 T2{Matrix2x3::CreateTranslationMatrix(m_OffsetSnapshot)};
    Matrix2x3 T1{Matrix2x3::CreateTranslationMatrix(m_pLevel->GetPlatform()->GetPosition<Vector2f>())};
    pos = T1 * T2 * pos;
    m_Shape.left = pos.orig.x;
}

void Player::UpdateState()
{
    // std::numeric_limits<float>::epsilon()
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};
    const float absVelX{std::abs(m_Velocity.x)};
    const float absVelY{std::abs(m_Velocity.y)};

    if (not m_Crouching and m_Velocity == Vector2f{})
    {
        m_State = State::idle;
    }
    else if (absVelX > 0.0f and absVelY < epsilon)
    {
        m_State = State::running;
    }
    else if (absVelX > 0.0f and absVelY > epsilon)
    {
        m_State = State::jumping_running;
        m_Crouching = false;
        m_CanClimb = false;
    }
    else if (absVelX < epsilon and absVelY > epsilon)
    {
        m_State = State::jumping_standing;
        m_Crouching = false;
        m_CanClimb = false;
    }

    if (m_Crouching)
    {
        m_State = State::crouching;
    }

    if (m_Attacking)
    {
        if (m_Crouching)
        {
            m_State = State::attacking_crouching;
        }
        else
        {
            m_State = State::attacking_normal;
        }
    }
    if (m_OnLadder)
    {
        m_State = State::climbing;
    }
}

// TODO: köze van a CheckForBoundaries függvényhez
void Player::UpdateCollisionBox()
{
    if (m_Crouching)
    {
        SetCollisionBoxHeight(44.0f);
    }
    else
    {
        ResetCollisionBox();
    }
    GameObject::UpdateCollisionBox();
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

int Player::GetLives() const
{
    return m_Lives;
}

Game::Label Player::GetWeapon() const
{
    return m_CurrWeapon;
}

int Player::GetScore() const
{
    return m_Score;
}

void Player::AddScore(int score)
{
    m_Score += score;
}

void Player::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;

    IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
    if (pEnemy)
    {
        m_pSoundManager->PlayEffect(Game::Label::E_ARTHUR_HIT);
        return;
    }
    IThrowable* pWeapon{dynamic_cast<IThrowable*>(other)};
    if (pWeapon)
    {
        m_pSoundManager->PlayEffect(Game::Label::E_WEAPON_PICKUP);
        switch (other->GetLabel())
        {
        case Game::Label::T_DAGGER:
            m_CurrWeapon = Game::Label::T_DAGGER;
            other->SetVisible(false);
            other->SetActive(false);
            break;
        case Game::Label::T_LANCE:
            m_CurrWeapon = Game::Label::T_LANCE;
            other->SetVisible(false);
            other->SetActive(false);
            break;
        case Game::Label::T_TORCH:
            m_CurrWeapon = Game::Label::T_TORCH;
            other->SetVisible(false);
            other->SetActive(false);
            break;
        case Game::Label::O_SHIELD:
            break;
        }
        return;
    }
    ICollectible* pCollectable{dynamic_cast<ICollectible*>(other)};
    if (pCollectable)
    {
        switch (other->GetLabel())
        {
        case Game::Label::O_KEY:
            break;
        case Game::Label::O_SHIELD:
            m_pSoundManager->PlayEffect(Game::Label::E_ARMOR_PICKUP);
            break;
        default:
            m_pSoundManager->PlayEffect(Game::Label::E_TREASURE_PICKUP);
            m_Score += pCollectable->GetScore();
            other->SetVisible(false);
            other->SetActive(false);
            break;
        }
        return;
    }
    IClimable* pClimable{dynamic_cast<IClimable*>(other)};
    if (pClimable)
    {
        m_OnLadder = true;
        return;
    }
    CollisionBox* pBox{dynamic_cast<CollisionBox*>(other)};
    if (pBox)
    {
        return;
    }
}

void Player::CheckForBoundaries(const Rectf& boundaries)
{
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
    const float epsilon{1.0f};
    if (m_CollisionBox.left < boundaries.left)
    {
        m_Shape.left = boundaries.left - horizontalOffset;
    }
    else if (m_CollisionBox.left + m_CollisionBox.width > boundaries.left + boundaries.width)
    {
        m_Shape.left = boundaries.left + boundaries.width - m_CollisionBox.width - horizontalOffset;
    }
}

Point2f Player::GetSpawnPos()
{
    return m_SpawnPos;
}
