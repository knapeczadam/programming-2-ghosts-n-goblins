// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Player.h"
#include "utils.h"
#include "IEnemy.h"
#include "level/Level.h"
#include "Texture.h"
#include "collectibles/ICollectible.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"

#include <iostream>
#include <numeric>

#include "Matrix2x3.h"
#include "level/Platform.h"
#include "weapons/Dagger.h"
#include "weapons/Lance.h"
#include "weapons/Torch.h"

const Point2f Player::m_SpawnPos{174.0f, 69.0f};

Player::Player(Sprite* pSprite, const Point2f& pos, Level* pLevel)
    : GameObject{Game::Label::C_ARTHUR, pSprite, pos}
      , m_HorVelocity{150.0f}
      , m_VerVelocity{500.0f}
      , m_Velocity{0.0f, 0.0f}
      , m_Acceleration{0.0f, -1391.0f} // -981.0f
      , m_State{State::idle}
      , m_pLevel{pLevel}
      , m_IsCrouching{false}
      , m_ShortAccuCooldown{0.0f}
      , m_LongAccuCooldown{0.0f}
      , m_ShortCooldownTime{0.25f}
      , m_LongCooldownTime{0.30f}
      , m_isAttacking{false}
      , m_Weapon{Game::Label::W_LANCE}
      , m_Overheated{false}
      , m_IsOnPlatform{false}
      , m_OffsetSnapshot{0.0f, 0.0f}
      , m_CanJump{true}
      , m_Lives{7}
      , m_MaxLives{7}
      , m_Score{14700}
{
}

void Player::valamiMegNemTom() const
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
        m_pSprite->SetFrameTime();
        break;
    case State::attacking_crouching:
        m_pSprite->SetTopOffsetRows(6);
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(2);
        m_pSprite->SetFramesPerSec(9);
        m_pSprite->SetFrameTime();
        break;
    case State::climbing:
        break;
    case State::climbing_top:
        break;
    }
    m_pSprite->SetCurrRowsCols();
    m_pSprite->UpdateSourceRect();
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
    if (m_isAttacking)
    {
        m_ShortAccuCooldown -= elapsedSec;
        if (m_ShortAccuCooldown < 0)
        {
            m_ShortAccuCooldown = 0;
            m_isAttacking = false;
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

void Player::Update(float elapsedSec)
{
    UpdateCooldown(elapsedSec);

    switch (m_State)
    {
    case State::climbing:
        break;
    case State::climbing_top:
        break;
    default:
        UpdatePosition(elapsedSec);
        break;
    }
    valamiMegNemTom();
    // late update
    UpdateCollisionBox();
    m_pSprite->Update(elapsedSec);
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

void Player::UpdatePosition(float elapsedSec)
{
    if (m_pLevel->IsOnGround(this))
    {
        const Uint8* pState{SDL_GetKeyboardState(nullptr)};
        Move(elapsedSec, pState);
    }
    UpdateState();

    ApplyGravity(elapsedSec);

    if (m_IsOnPlatform)
    {
        SyncWithPlatform(elapsedSec);
    }
    else
    {
        m_OffsetSnapshot = Vector2f{0, 0};
        m_Shape.left += m_Velocity.x * elapsedSec;
        m_Shape.bottom += m_Velocity.y * elapsedSec;
    }

    CheckForBoundaries(m_pLevel->GetBoundaries());
}

void Player::UpdateState()
{
    // std::numeric_limits<float>::epsilon()
    constexpr float epsilon{std::numeric_limits<float>::epsilon()};
    const float absVelX{std::abs(m_Velocity.x)};
    const float absVelY{std::abs(m_Velocity.y)};

    if (not m_IsCrouching and m_Velocity == Vector2f{})
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
        m_IsCrouching = false;
    }
    else if (absVelX < epsilon and absVelY > epsilon)
    {
        m_State = State::jumping_standing;
        m_IsCrouching = false;
    }

    if (m_IsCrouching)
    {
        m_State = State::crouching;
    }

    if (m_isAttacking)
    {
        if (m_IsCrouching)
        {
            m_State = State::attacking_crouching;
        }
        else
        {
            m_State = State::attacking_normal;
        }
    }
}

void Player::Move(float elapsedSec, const Uint8* pState)
{
    Crouch(pState);
    if (m_IsCrouching or m_isAttacking)
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
        m_IsFlipped = true;
    }
    else if (pState[SDL_SCANCODE_RIGHT])
    {
        m_Velocity.x = m_HorVelocity;
        m_IsFlipped = false;
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
            m_Velocity.y = m_VerVelocity;
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
        m_IsCrouching = true;
    }
    else
    {
        m_IsCrouching = false;
    }
}

void Player::Attack(std::vector<IThrowable*>& throwables, SpriteFactory* spriteFactory)
{
    if (not m_isAttacking)
    {
        m_ShortAccuCooldown += m_ShortCooldownTime;
        m_LongAccuCooldown += m_LongCooldownTime;
        m_isAttacking = true;

        switch (m_Weapon)
        {
        case Game::Label::W_DAGGER:
            throwables.push_back(new Dagger{spriteFactory->CreateSprite(m_Weapon), GetShapeCenter(), m_IsFlipped});
            break;
        case Game::Label::W_LANCE:
            throwables.push_back(new Lance{spriteFactory->CreateSprite(m_Weapon), GetShapeCenter(), m_IsFlipped});
            break;
        case Game::Label::W_TORCH:
            throwables.push_back(new Torch{spriteFactory->CreateSprite(m_Weapon), GetShapeCenter(), m_IsFlipped});
            break;
        }
    }
}

void Player::Climb(const Uint8* pState)
{
    if (pState[SDL_SCANCODE_UP])
    {
    }
    else if (pState[SDL_SCANCODE_DOWN])
    {
    }
}

bool Player::IsAttacking() const
{
    return m_isAttacking;
}

void Player::CanJump(bool canJump)
{
    m_CanJump = canJump;
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
    m_IsOnPlatform = isOnPlatform;
}

int Player::GetLives() const
{
    return m_Lives;
}

Game::Label Player::GetWeapon() const
{
    return m_Weapon;
}

int Player::GetScore() const
{
    return m_Score;
}

void Player::ApplyGravity(float elapsedSec)
{
    m_Velocity += m_Acceleration * elapsedSec;
}

void Player::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;

    IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
    if (pEnemy)
    {
    }
    ICollectible* pCollectible{dynamic_cast<ICollectible*>(other)};
    if (pCollectible)
    {
        switch (other->GetLabel())
        {
        case Game::Label::W_DAGGER:
            m_Weapon = Game::Label::W_DAGGER;
            other->SetVisible(false);
            other->SetActive(false);
            break;
        case Game::Label::W_LANCE:
            m_Weapon = Game::Label::W_LANCE;
            break;
        case Game::Label::W_TORCH:
            m_Weapon = Game::Label::W_TORCH;
            break;
        case Game::Label::O_SHIELD:
            break;
        }
    }
}

void Player::CheckForBoundaries(const Rectf& boundaries)
{
    const float horizontalOffset{(m_Shape.width - m_pSprite->GetCollisionWidth()) / 2};
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
