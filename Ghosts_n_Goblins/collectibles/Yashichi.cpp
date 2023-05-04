#include "pch.h"
#include "Yashichi.h"

Yashichi::Yashichi(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_STAR, pSprite, pos}
{
    m_Score = 10000;
}
