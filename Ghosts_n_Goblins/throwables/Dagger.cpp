﻿#include "pch.h"
#include "Dagger.h"

#include "engine/Sprite.h"


Dagger::Dagger(const Point2f& pos, bool isFlipped, bool collectible, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::T_DAGGER, pos, true, pSpriteFactory}
      , m_Speed{300.0f}
      , m_Collectible{collectible}
{
    m_Flipped = isFlipped;
    SetSprite();
}

void Dagger::Update(float elapsedSec)
{
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
    UpdateCollisionBox();
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