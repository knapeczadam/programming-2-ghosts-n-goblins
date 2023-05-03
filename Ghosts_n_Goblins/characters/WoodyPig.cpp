#include "pch.h"
#include "WoodyPig.h"

#include "weapons/IThrowable.h"

WoodyPig::WoodyPig(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_WOODY_PIG, pSprite, pos}
{
    m_Score = 100;
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
}
