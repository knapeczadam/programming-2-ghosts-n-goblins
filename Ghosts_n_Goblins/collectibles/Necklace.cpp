#include "pch.h"
#include "Necklace.h"

Necklace::Necklace(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::NECKLACE, pSprite, pos}
{
}

void Necklace::Draw() const
{
    GameObject::Draw();
}

void Necklace::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}
