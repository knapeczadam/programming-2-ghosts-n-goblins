#include "pch.h"
#include "FlyingKnight.h"

#include "weapons/IThrowable.h"

FlyingKnight::FlyingKnight(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::FLYING_KNIGHT, pSprite, pos}
{
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
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(other)};
    if (pThrowable)
    {
    }
}
