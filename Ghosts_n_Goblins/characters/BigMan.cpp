#include "pch.h"
#include "BigMan.h"

#include "weapons/IThrowable.h"

class Sprite;

BigMan::BigMan(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_BIG_MAN, pSprite, pos}
{
    m_Score = 2000;
}

void BigMan::Draw() const
{
    GameObject::Draw();
}

void BigMan::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void BigMan::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
}