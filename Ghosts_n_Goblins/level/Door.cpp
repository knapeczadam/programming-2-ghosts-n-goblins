#include "pch.h"
#include "Door.h"

#include "engine/Sprite.h"

Door::Door(const Point2f& pos, GameController* pGameController)
    : GameObject(Game::Label::L_DOOR, pos, false, pGameController)
{
}

void Door::Update(float elapsedSec)
{
    if (m_pSprite->GetIterCount() == 0 and m_pSprite->IsLastFrame())
    {
        m_Active = false;
    }
}
