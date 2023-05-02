#include "pch.h"
#include "Dagger.h"

#include "engine/Sprite.h"


Dagger::Dagger(Sprite* pSprite, const Point2f& pos, bool isFlipped)
    : GameObject{Game::Label::W_DAGGER, pSprite, pos}
    , m_Speed{300.0f}
{
    m_IsFlipped = isFlipped;
}

void Dagger::Update(float elapsedSec)
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
