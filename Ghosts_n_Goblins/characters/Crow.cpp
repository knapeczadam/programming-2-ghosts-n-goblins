#include "pch.h"
#include "Crow.h"

#include "weapons/IThrowable.h"

Crow::Crow(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::CROW, pSprite, pos}
{
}

void Crow::Draw() const
{
    GameObject::Draw();
}

void Crow::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void Crow::HandleCollision(GameObject* player)
{
    if (not IsOverlapping(player)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(player)};
    if (pThrowable)
    {
    }
}
