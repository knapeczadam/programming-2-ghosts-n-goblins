﻿#include "pch.h"
#include "Crow.h"

#include "weapons/IThrowable.h"

Crow::Crow(Sprite* pSprite, const Point2f& pos)
    : GameObject{Game::Label::C_CROW, pSprite, pos}
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

void Crow::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    
    IThrowable* pThrowable{dynamic_cast<IThrowable*>(other)};
    if (pThrowable)
    {
    }
}