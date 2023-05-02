#include "pch.h"
#include "Water.h"
#include "characters/Player.h"
#include "engine/Sprite.h"

#include <iostream>

Water::Water(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::L_WATER, pSprite, pos}
{
}

Water::Water(Sprite* pSprite, const Point2f& pos, float clipWidth)
    : GameObject{Game::Label::L_WATER, pSprite, pos}
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
