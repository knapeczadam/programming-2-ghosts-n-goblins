#include "pch.h"
#include "Lance.h"

#include "engine/Sprite.h"

Lance::Lance(Sprite* pSprite, const Point2f& pos, bool isFlipped)
    : GameObject{Game::Label::W_LANCE, pSprite, pos}
        , m_Speed{300.0f}
{   
    m_IsFlipped = isFlipped;
}

void Lance::Update(float elapsedSec)
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
