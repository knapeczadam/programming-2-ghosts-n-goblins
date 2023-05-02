#include "pch.h"
#include "Torch.h"
#include "engine/Sprite.h"


Torch::Torch(Sprite* pSprite, const Point2f& pos, bool isFlipped)
    : GameObject{Game::Label::W_TORCH, pSprite, pos}
    , m_Speed{300.0f}
{
    m_IsFlipped = isFlipped;
}

void Torch::Update(float elapsedSec)
{
    if (m_IsFlipped)
    {
        m_Shape.left -= m_Speed * elapsedSec;
    }
    else
    {
        m_Shape.left += m_Speed * elapsedSec;
    }
}