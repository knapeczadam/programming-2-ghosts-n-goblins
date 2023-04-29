#include "pch.h"
#include "WoodyPig.h"

#include "weapons/IThrowable.h"

WoodyPig::WoodyPig(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::WOODY_PIG, pSprite, pos}
{
}

void WoodyPig::Draw() const
{
    GameObject::Draw();
}

void WoodyPig::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void WoodyPig::HandleCollision(GameObject* player)
{
    if (not IsOverlapping(player)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(player)};
    if (pThrowable)
    {
    }
}
