#include "pch.h"
#include "GreenMonster.h"

#include "weapons/IThrowable.h"

GreenMonster::GreenMonster(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_GREEN_MONSTER, pSprite, pos}
{
    m_Score = 100;
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
}
