#include "pch.h"
#include "Torch.h"

#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/LevelManager.h"
#include "level/Level.h"

Torch::Torch(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController)
    : GameObject{collectible ? Game::Label::O_TORCH : Game::Label::T_TORCH, pos, true, pGameController}
    , m_Collectible{collectible}
{
    m_Speed.x = 400.0f;
    m_Speed.y = -1091.0f;
    m_Angle = 30.0f * utils::g_Pi / 180.0f;
    m_Flipped = isFlipped;
    m_AwakeDistance = std::numeric_limits<float>::max();
}

void Torch::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    m_AccuTime += elapsedSec;
    if (m_Collectible)
    {
        return;
    }
    if (m_Flipped)
    {
        m_Shape.left = m_OriginalPos.x +  -m_Speed.x * std::cos(m_Angle) * m_AccuTime;
    }
    else
    {
        m_Shape.left = m_OriginalPos.x + m_Speed.x * std::cos(m_Angle) * m_AccuTime;
    }
    m_Shape.bottom = m_OriginalPos.y +  m_Speed.x * std::sin(m_Angle) * m_AccuTime +  0.5f * m_Speed.y * m_AccuTime * m_AccuTime;

    if (m_pGameController->m_pLevelManager->GetLevel()->IsOnGround(this))
    {
        m_Active = false;
        m_Visible = false;
        Point2f pos;
        pos.x = GetColliderCenter().x;
        pos.y = GetCollider().bottom;
        m_pGameController->m_pFXManager->PlayEffect(Game::Label::F_FIRE_TORCH, pos, false);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_TORCH);
    }
}

void Torch::Awake(float elapsedSec)
{
    if (not m_Collectible)
    {
        const Point2f pos{GetPosition<Point2f>()};
        m_Shape.left = pos.x;
        m_Shape.bottom = pos.y;
    }
    if (not m_Collectible and m_Flipped)
    {
        m_Shape.left -= m_pSprite->GetScaledClipWidth();
    }
    m_OriginalPos.x = m_Shape.left;
    m_OriginalPos.y = m_Shape.bottom;
}

void Torch::Reset()
{
    GameObject::Reset();
    m_AccuTime = 0.0f;
    UpdateCollider();
}
