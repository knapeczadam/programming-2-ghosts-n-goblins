#include "pch.h"
#include "Torch.h"

#include "engine/Sprite.h"

Torch::Torch(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController)
    : GameObject{collectible ? Game::Label::O_TORCH : Game::Label::T_TORCH, pos, true, pGameController}
    , m_Collectible{collectible}
{
    m_Speed = 300.0f;
    m_Flipped = isFlipped;
    m_AwakeDistance = std::numeric_limits<float>::max();
    if (not collectible)
    {
        m_Shape.left = pos.x;
        m_Shape.bottom = pos.y;
    }
}

void Torch::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    if (m_Collectible)
    {
        return;
    }
    if (m_Flipped)
    {
        m_Shape.left -= m_Speed * elapsedSec;
    }
    else
    {
        m_Shape.left += m_Speed * elapsedSec;
    }
}

void Torch::Awake(float elapsedSec)
{
    if (not m_Collectible and m_Flipped)
    {
        m_Shape.left -= m_pSprite->GetScaledClipWidth();
    }
}