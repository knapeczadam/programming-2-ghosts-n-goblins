#include "pch.h"
#include "GreenMonster.h"

#include "weapons/IThrowable.h"

GreenMonster::GreenMonster(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::GREEN_MONSTER, pSprite, pos}
{
}

void GreenMonster::Draw() const
{
    GameObject::Draw();
}

void GreenMonster::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void GreenMonster::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(other)};
    if (pThrowable)
    {
    }
}
