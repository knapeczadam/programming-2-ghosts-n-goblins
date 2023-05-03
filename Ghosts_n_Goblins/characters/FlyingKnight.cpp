#include "pch.h"
#include "FlyingKnight.h"

#include "weapons/IThrowable.h"

FlyingKnight::FlyingKnight(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_FLYING_KNIGHT, pSprite, pos}
{
    m_Score = 100;
}

void FlyingKnight::Draw() const
{
    GameObject::Draw();
}

void FlyingKnight::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void FlyingKnight::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
}
