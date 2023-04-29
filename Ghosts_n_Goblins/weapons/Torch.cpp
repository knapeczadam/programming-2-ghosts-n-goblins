#include "pch.h"
#include "Torch.h"

Torch::Torch(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::TORCH, pSprite, pos}
{
}

void Torch::Draw() const
{
    GameObject::Draw();
}

void Torch::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}
