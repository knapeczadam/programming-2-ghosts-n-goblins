#include "pch.h"
#include "Key.h"

Key::Key(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_KEY, pos, true, pGameController}
{
    m_Score = 1000;
}
