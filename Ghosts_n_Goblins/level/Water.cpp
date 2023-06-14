#include "pch.h"
#include "Water.h"

#include "characters/Player.h"
#include "engine/Sprite.h"

Water::Water(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::L_WATER, pos, false, pGameController}
{
}

Water::Water(const Point2f& pos, float clipWidth, GameController* pGameController)
    : GameObject{Game::Label::L_WATER, pos, false, pGameController}
{
    m_pSprite->SetClipWidth(clipWidth);
}
