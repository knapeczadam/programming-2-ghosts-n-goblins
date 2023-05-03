#include "pch.h"
#include "Key.h"

Key::Key(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::O_KEY, pSprite, pos}
{
    m_Score = 1000;
}
