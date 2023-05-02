#include "pch.h"
#include "WoodyPig.h"

#include "weapons/IThrowable.h"

WoodyPig::WoodyPig(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_WOODY_PIG, pSprite, pos}
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

void WoodyPig::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(other)};
    if (pThrowable)
    {
    }
}
