#include "pch.h"
#include "Yashichi.h"

Yashichi::Yashichi(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::O_YASHICHI, pos, true, pSpriteFactory}
{
    m_Score = 10000;
}
