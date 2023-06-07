#include "pch.h"
#include "Lance.h"

#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"

Lance::Lance(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController)
    : GameObject{Game::Label::T_LANCE, pos, true, pGameController}
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
    SetSprite();
}

void Lance::Update(float elapsedSec)
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

void Lance::Awake(float elapsedSec)
{
    if (not m_Collectible and m_Flipped)
    {
        m_Shape.left -= m_pSprite->GetScaledClipWidth();
    }
}

void Lance::SetSprite() const
{
    if (m_Collectible)
    {
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(3);
    }
    else
    {
        m_pSprite->SetSubRows(1);
        m_pSprite->SetSubCols(1);
    }
    m_pSprite->SetCurrRowsCols();
}
