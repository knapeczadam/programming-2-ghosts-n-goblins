#include "pch.h"
#include "BigMan.h"

#include "weapons/IThrowable.h"

BigMan::BigMan(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::BIG_MAN, pSprite, pos}
{
}

void BigMan::Draw() const
{
    GameObject::Draw();
}

void BigMan::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void BigMan::HandleCollision(GameObject* player)
{
    if (not IsOverlapping(player)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(player)};
    if (pThrowable)
    {
    }
}