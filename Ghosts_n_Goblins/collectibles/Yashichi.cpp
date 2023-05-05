#include "pch.h"
#include "Yashichi.h"

Yashichi::Yashichi(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_YASHICHI, pos, true, pGameController}
{
    m_Score = 10000;
}
