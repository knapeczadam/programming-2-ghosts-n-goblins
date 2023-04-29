#include "pch.h"
#include "Water.h"
#include "characters/Player.h"

Water::Water(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::WATER, pSprite, pos}
{
}

void Water::Draw() const
{
    GameObject::Draw();
}

void Water::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Water::HandleCollision(GameObject* player)
{
    Player* pPlayer{ static_cast<Player*>(player) };
}
