#include "pch.h"
#include "Dagger.h"

#include "engine/Sprite.h"

Dagger::Dagger(const Point2f& pos, bool isFlipped, bool collectible, GameController* pGameController)
    : GameObject{Game::Label::T_DAGGER, pos, true, pGameController}
    , m_Collectible{collectible}
{
    m_Speed.x = 350.0f;
    m_Flipped = isFlipped;
    m_AwakeDistance = std::numeric_limits<float>::max();
    if (not m_Collectible)
    {
        m_Shape.left = pos.x;
        m_Shape.bottom = pos.y;
    }
    SetSprite();
}

void Dagger::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
    if (m_Collectible)
    {
        return;
    }
    if (m_Flipped)
    {
        m_Shape.left -= m_Speed.x * elapsedSec;
    }
    else
    {
        m_Shape.left += m_Speed.x * elapsedSec;
    }
}

void Dagger::Awake(float elapsedSec)
{
    if (not m_Collectible and m_Flipped)
    {
        m_Shape.left -= m_pSprite->GetScaledClipWidth();
    }
}

void Dagger::SetSprite() const
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
