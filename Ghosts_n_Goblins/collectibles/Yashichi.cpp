#include "pch.h"
#include "Yashichi.h"

Yashichi::Yashichi(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_YASHICHI, pSprite, pos}
{
    m_Score = 10000;
}
