#include "pch.h"
#include "Magician.h"

Magician::Magician(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::E_MAGICIAN, pSprite, pos}
{
    m_Score = 2000;
}

void Magician::Draw() const
{
    GameObject::Draw();
}

void Magician::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Magician::HandleCollision(GameObject* other)
{
    GameObject::HandleCollision(other);
}
