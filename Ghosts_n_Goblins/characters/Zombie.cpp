#include "pch.h"
#include "Zombie.h"

Zombie::Zombie(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_ZOMBIE, pSprite, pos}
{
    m_Score = 200;
}

void Zombie::Draw() const
{
    GameObject::Draw();
}

void Zombie::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Zombie::HandleCollision(GameObject* other)
{
    GameObject::HandleCollision(other);
}
