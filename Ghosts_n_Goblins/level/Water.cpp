#include "pch.h"
#include "Water.h"
#include "characters/Player.h"
#include "engine/Sprite.h"

#include <iostream>

Water::Water(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::WATER, pSprite, pos}
{
}

Water::Water(Sprite* pSprite, const Point2f& pos, float clipWidth)
    : GameObject{Game::Label::WATER, pSprite, pos}
{
    m_pSprite->SetClipWidth(clipWidth);
}

void Water::Draw() const
{
    GameObject::Draw();
}

void Water::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Water::HandleCollision(GameObject* other)
{
    Player* pPlayer{ static_cast<Player*>(other) };
}
