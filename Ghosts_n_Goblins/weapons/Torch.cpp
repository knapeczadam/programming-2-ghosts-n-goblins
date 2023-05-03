#include "pch.h"
#include "Torch.h"
#include "engine/Sprite.h"


Torch::Torch(Sprite* pSprite, const Point2f& pos, bool isFlipped, bool collectible)
    : GameObject{Game::Label::W_TORCH, pSprite, pos}
    , m_Speed{300.0f}
    , m_Collectible{collectible}
{
    m_Flipped = isFlipped;
    SetSprite();
}

void Torch::Update(float elapsedSec)
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
}

void Torch::SetSprite() const
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
