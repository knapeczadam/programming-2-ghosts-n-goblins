#include "pch.h"
#include "Dagger.h"

#include "engine/Sprite.h"

Dagger::Dagger(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::DAGGER, pSprite, pos}
{
}

void Dagger::Draw() const
{
    GameObject::Draw();
}

void Dagger::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}