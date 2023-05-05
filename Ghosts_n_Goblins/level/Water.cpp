#include "pch.h"
#include "Water.h"
#include "characters/Player.h"
#include "engine/Sprite.h"

#include <iostream>

Water::Water(const Point2f& pos, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::L_WATER, pos, false, pSpriteFactory}
{
}

Water::Water(const Point2f& pos, float clipWidth, SpriteFactory* pSpriteFactory)
    : GameObject{Game::Label::L_WATER, pos, false, pSpriteFactory}
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
