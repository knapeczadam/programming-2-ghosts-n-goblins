#include "pch.h"
#include "RedArremer.h"

#include "weapons/IThrowable.h"

RedArremer::RedArremer(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::RED_ARREMER, pSprite, pos}
{
}

void RedArremer::Draw() const
{
    GameObject::Draw();
}

void RedArremer::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void RedArremer::HandleCollision(GameObject* player)
{
    if (not IsOverlapping(player)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(player)};
    if (pThrowable)
    {
    }
}
